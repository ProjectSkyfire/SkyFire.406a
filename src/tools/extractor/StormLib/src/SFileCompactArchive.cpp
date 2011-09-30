/*****************************************************************************/
/* SFileCompactArchive.cpp                Copyright (c) Ladislav Zezula 2003 */
/*---------------------------------------------------------------------------*/
/* Archive compacting function                                               */
/*---------------------------------------------------------------------------*/
/*   Date    Ver   Who  Comment                                              */
/* --------  ----  ---  -------                                              */
/* 14.04.03  1.00  Lad  Splitted from SFileCreateArchiveEx.cpp               */
/* 19.11.03  1.01  Dan  Big endian handling                                  */
/*****************************************************************************/

#define __STORMLIB_SELF__
#include "StormLib.h"
#include "StormCommon.h"

/*****************************************************************************/
/* Local variables                                                           */
/*****************************************************************************/

static SFILE_COMPACT_CALLBACK CompactCB = NULL;
static ULONGLONG CompactBytesProcessed = 0;
static ULONGLONG CompactTotalBytes = 0;
static void * pvUserData = NULL;

/*****************************************************************************/
/* Local functions                                                           */
/*****************************************************************************/

static int CheckIfAllFilesKnown(TMPQArchive * ha, const char * szListFile, LPDWORD pFileKeys)
{
    TFileEntry * pFileTableEnd;
    TFileEntry * pFileEntry;
    DWORD dwBlockIndex = 0;
    int nError = ERROR_SUCCESS;

    // Add the listfile to the MPQ
    if (nError == ERROR_SUCCESS && szListFile != NULL)
    {
        // Notify the user
        if (CompactCB != NULL)
            CompactCB(pvUserData, CCB_CHECKING_FILES, CompactBytesProcessed, CompactTotalBytes);

        if (!SFileAddListFile((HANDLE)ha, szListFile))
            nError = ERROR_CAN_NOT_COMPLETE;
    }

    // Verify the file table
    if (nError == ERROR_SUCCESS)
    {
        pFileTableEnd = ha->pFileTable + ha->dwFileTableSize;
        for (pFileEntry = ha->pFileTable; pFileEntry < pFileTableEnd; pFileEntry++, dwBlockIndex++)
        {
            if (pFileEntry->dwFlags & MPQ_FILE_EXISTS)
            {
                if (pFileEntry->szFileName != NULL && !IsPseudoFileName(pFileEntry->szFileName, NULL))
                {
                    DWORD dwFileKey = 0;

                    // Resolve the file key. Use plain file name for it
                    if (pFileEntry->dwFlags & MPQ_FILE_ENCRYPTED)
                    {
                        dwFileKey = DecryptFileKey(pFileEntry->szFileName, 
                                                   pFileEntry->ByteOffset, 
                                                   pFileEntry->dwFileSize, 
                                                   pFileEntry->dwFlags);
                    }

                    // Give the key to the caller
                    if (pFileKeys != NULL)
                        pFileKeys[dwBlockIndex] = dwFileKey;
                }
                else
                {
                    nError = ERROR_CAN_NOT_COMPLETE;
                    break;
                }
            }
        }
    }

    return nError;
}

static int CopyNonMpqData(
    TFileStream * pSrcStream, 
    TFileStream * pTrgStream, 
    ULONGLONG & ByteOffset, 
    ULONGLONG & ByteCount)
{
    ULONGLONG DataSize = ByteCount;
    DWORD dwToRead;
    char DataBuffer[0x1000];
    int nError = ERROR_SUCCESS;

    // Copy the data
    while (DataSize > 0)
    {
        // Get the proper size of data
        dwToRead = sizeof(DataBuffer);
        if (DataSize < dwToRead)
            dwToRead = (DWORD)DataSize;

        // Read from the source stream
        if (!FileStream_Read(pSrcStream, &ByteOffset, DataBuffer, dwToRead))
        {
            nError = GetLastError();
            break;
        }

        // Write to the target stream
        if (!FileStream_Write(pTrgStream, NULL, DataBuffer, dwToRead))
        {
            nError = GetLastError();
            break;
        }

        // Update the progress
        if (CompactCB != NULL)
        {
            CompactBytesProcessed += dwToRead;
            CompactCB(pvUserData, CCB_COPYING_NON_MPQ_DATA, CompactBytesProcessed, CompactTotalBytes);
        }

        // Decrement the number of data to be copied
        ByteOffset += dwToRead;
        DataSize -= dwToRead;
    }

    return ERROR_SUCCESS;
}

// Copies all file sectors into another archive.
static int CopyMpqFileSectors(
    TMPQArchive * ha, 
    TMPQFile * hf, 
    TFileStream * pNewStream)
{
    TFileEntry * pFileEntry = hf->pFileEntry;
    ULONGLONG RawFilePos;               // Used for calculating sector offset in the old MPQ archive
    ULONGLONG MpqFilePos;               // MPQ file position in the new archive
    DWORD dwBytesToCopy = pFileEntry->dwCmpSize;
    DWORD dwFileKey1 = 0;               // File key used for decryption
    DWORD dwFileKey2 = 0;               // File key used for encryption
    DWORD dwCmpSize = 0;                // Compressed file size
    int nError = ERROR_SUCCESS;

    // Remember the position in the destination file
    FileStream_GetPos(pNewStream, MpqFilePos);
    MpqFilePos -= ha->MpqPos;

    // Resolve decryption keys. Note that the file key given
    // in the TMPQFile structure also includes the key adjustment
    if (nError == ERROR_SUCCESS && (pFileEntry->dwFlags & MPQ_FILE_ENCRYPTED))
    {
        dwFileKey2 = dwFileKey1 = hf->dwFileKey;
        if (pFileEntry->dwFlags & MPQ_FILE_FIX_KEY)
        {
            dwFileKey2 = (dwFileKey1 ^ pFileEntry->dwFileSize) - (DWORD)pFileEntry->ByteOffset;
            dwFileKey2 = (dwFileKey2 + (DWORD)MpqFilePos) ^ pFileEntry->dwFileSize;
        }
    }

    // If we have to save patch header, do it
    if (nError == ERROR_SUCCESS && hf->PatchInfo != NULL)
    {
        BSWAP_ARRAY32_UNSIGNED(hf->PatchInfo, sizeof(DWORD) * 3);
        if (!FileStream_Write(pNewStream, NULL, hf->PatchInfo, hf->PatchInfo->dwLength))
            nError = GetLastError();

        // Note: In wow-update-12694.MPQ, the dwCmpSize doesn't
        // include the patch header on some files.
        dwCmpSize += hf->PatchInfo->dwLength;
    }

    // If we have to save sector offset table, do it.
    if (nError == ERROR_SUCCESS && hf->SectorOffsets != NULL)
    {
        LPDWORD SectorOffsetsCopy = ALLOCMEM(DWORD, hf->dwSectorCount);
        DWORD dwSectorPosLen = hf->dwSectorCount * sizeof(DWORD);

        assert((pFileEntry->dwFlags & MPQ_FILE_SINGLE_UNIT) == 0);
        assert(pFileEntry->dwFlags & MPQ_FILE_COMPRESSED);

        if (SectorOffsetsCopy == NULL)
            nError = ERROR_NOT_ENOUGH_MEMORY;

        // Encrypt the secondary sector offset table and write it to the target file
        if (nError == ERROR_SUCCESS)
        {
            memcpy(SectorOffsetsCopy, hf->SectorOffsets, dwSectorPosLen);
            if (pFileEntry->dwFlags & MPQ_FILE_ENCRYPTED)
                EncryptMpqBlock(SectorOffsetsCopy, dwSectorPosLen, dwFileKey2 - 1);

            BSWAP_ARRAY32_UNSIGNED(SectorOffsetsCopy, dwSectorPosLen);
            if (!FileStream_Write(pNewStream, NULL, SectorOffsetsCopy, dwSectorPosLen))
                nError = GetLastError();

            dwCmpSize += dwSectorPosLen;
        }

        // Update compact progress
        if (CompactCB != NULL)
        {
            CompactBytesProcessed += dwSectorPosLen;
            CompactCB(pvUserData, CCB_COMPACTING_FILES, CompactBytesProcessed, CompactTotalBytes);
        }

        FREEMEM(SectorOffsetsCopy);
    }

    // Now we have to copy all file sectors. We do it without
    // recompression, because recompression is not necessary in this case
    if (nError == ERROR_SUCCESS)
    {
        for (DWORD dwSector = 0; dwSector < hf->dwDataSectors; dwSector++)
        {
            DWORD dwRawDataInSector = hf->dwSectorSize;
            DWORD dwRawByteOffset = dwSector * hf->dwSectorSize;

            // Last sector: If there is not enough bytes remaining in the file, cut the raw size
            if (dwRawDataInSector > dwBytesToCopy)
                dwRawDataInSector = dwBytesToCopy;

            // Fix the raw data length if the file is compressed
            if (hf->SectorOffsets != NULL)
            {
                dwRawDataInSector = hf->SectorOffsets[dwSector+1] - hf->SectorOffsets[dwSector];
                dwRawByteOffset = hf->SectorOffsets[dwSector];
            }

            // Calculate the raw file offset of the file sector
            CalculateRawSectorOffset(RawFilePos, hf, dwRawByteOffset);

            // Read the file sector
            if (!FileStream_Read(ha->pStream, &RawFilePos, hf->pbFileSector, dwRawDataInSector))
            {
                nError = GetLastError();
                break;
            }

            // If necessary, re-encrypt the sector
            // Note: Recompression is not necessary here. Unlike encryption, 
            // the compression does not depend on the position of the file in MPQ.
            if ((pFileEntry->dwFlags & MPQ_FILE_ENCRYPTED) && dwFileKey1 != dwFileKey2)
            {
                BSWAP_ARRAY32_UNSIGNED(hf->pbFileSector, dwRawDataInSector);
                DecryptMpqBlock(hf->pbFileSector, dwRawDataInSector, dwFileKey1 + dwSector);
                EncryptMpqBlock(hf->pbFileSector, dwRawDataInSector, dwFileKey2 + dwSector);
                BSWAP_ARRAY32_UNSIGNED(hf->pbFileSector, dwRawDataInSector);
            }

            // Now write the sector back to the file
            if (!FileStream_Write(pNewStream, NULL, hf->pbFileSector, dwRawDataInSector))
            {
                nError = GetLastError();
                break;
            }

            // Update compact progress
            if (CompactCB != NULL)
            {
                CompactBytesProcessed += dwRawDataInSector;
                CompactCB(pvUserData, CCB_COMPACTING_FILES, CompactBytesProcessed, CompactTotalBytes);
            }

            // Adjust byte counts
            dwBytesToCopy -= hf->dwSectorSize;
            dwCmpSize += dwRawDataInSector;
        }
    }

    // Copy the sector CRCs, if any
    // Sector CRCs are always compressed (not imploded) and unencrypted
    if (nError == ERROR_SUCCESS && hf->SectorOffsets != NULL && hf->SectorChksums != NULL)
    {
        DWORD dwCrcLength;

        dwCrcLength = hf->SectorOffsets[hf->dwSectorCount - 1] - hf->SectorOffsets[hf->dwSectorCount - 2];
        if (dwCrcLength != 0)
        {
            if (!FileStream_Read(ha->pStream, NULL, hf->SectorChksums, dwCrcLength))
                nError = GetLastError();

            if (!FileStream_Write(pNewStream, NULL, hf->SectorChksums, dwCrcLength))
                nError = GetLastError();

            // Update compact progress
            if (CompactCB != NULL)
            {
                CompactBytesProcessed += dwCrcLength;
                CompactCB(pvUserData, CCB_COMPACTING_FILES, CompactBytesProcessed, CompactTotalBytes);
            }

            // Size of the CRC block is also included in the compressed file size
            dwCmpSize += dwCrcLength;
        }
    }

    // Update file position in the block table
    if (nError == ERROR_SUCCESS)
    {
        // At this point, number of bytes written should be exactly
        // the same like the compressed file size. If it isn't, 
        // there's something wrong (an unknown archive version, MPQ protection, ...)
        //
        // Note: Diablo savegames have very weird layout, and the file "hero"
        // seems to have improper compressed size. Instead of real compressed size, 
        // the "dwCmpSize" member of the block table entry contains
        // uncompressed size of file data + size of the sector table.
        // If we compact the archive, Diablo will refuse to load the game
        // Seems like some sort of protection to me.
        if (dwCmpSize == pFileEntry->dwCmpSize)
        {
            // Update file pos in the block table
            pFileEntry->ByteOffset = MpqFilePos;
        }
        else
        {
            nError = ERROR_FILE_CORRUPT;
            assert(false);
        }
    }

    return nError;
}

static int CopyMpqFiles(TMPQArchive * ha, LPDWORD pFileKeys, TFileStream * pNewStream)
{
    TFileEntry * pFileTableEnd = ha->pFileTable + ha->dwFileTableSize;
    TFileEntry * pFileEntry;
    TMPQFile * hf = NULL;
    int nError = ERROR_SUCCESS;

    // Walk through all files and write them to the destination MPQ archive
    for (pFileEntry = ha->pFileTable; pFileEntry < pFileTableEnd; pFileEntry++)
    {
        // Copy all the file sectors
        // Only do that when the file has nonzero size
        if ((pFileEntry->dwFlags & MPQ_FILE_EXISTS) && pFileEntry->dwFileSize != 0)
        {
            // Allocate structure for the MPQ file
            hf = CreateMpqFile(ha);
            if (hf == NULL)
                return ERROR_NOT_ENOUGH_MEMORY;

            // Store file entry
            hf->pFileEntry = pFileEntry;

            // Set the raw file position
            hf->MpqFilePos = pFileEntry->ByteOffset;
            hf->RawFilePos = ha->MpqPos + hf->MpqFilePos;

            // Set the file decryption key
            hf->dwFileKey = pFileKeys[pFileEntry - ha->pFileTable];
            hf->dwDataSize = pFileEntry->dwFileSize;

            // If the file is a patch file, load the patch header
            if (pFileEntry->dwFlags & MPQ_FILE_PATCH_FILE)
            {
                nError = AllocatePatchInfo(hf, true);
                if (nError != ERROR_SUCCESS)
                    break;
            }

            // Allocate buffers for file sector and sector offset table
            nError = AllocateSectorBuffer(hf);
            if (nError != ERROR_SUCCESS)
                break;

            // Also allocate sector offset table and sector checksum table
            nError = AllocateSectorOffsets(hf, true);
            if (nError != ERROR_SUCCESS)
                break;

            // Also load sector checksums, if any
            if (pFileEntry->dwFlags & MPQ_FILE_SECTOR_CRC)
            {
                nError = AllocateSectorChecksums(hf, false);
                if (nError != ERROR_SUCCESS)
                    break;
            }

            // Copy all file sectors
            nError = CopyMpqFileSectors(ha, hf, pNewStream);
            if (nError != ERROR_SUCCESS)
                break;

            // Free buffers. This also sets "hf" to NULL.
            FreeMPQFile(hf);
        }
    }

    // Cleanup and exit
    if (hf != NULL)
        FreeMPQFile(hf);
    return nError;
}

/*****************************************************************************/
/* Public functions                                                          */
/*****************************************************************************/

bool WINAPI SFileSetCompactCallback(HANDLE /* hMpq */, SFILE_COMPACT_CALLBACK aCompactCB, void * pvData)
{
    CompactCB = aCompactCB;
    pvUserData = pvData;
    return true;
}

//-----------------------------------------------------------------------------
// Archive compacting

bool WINAPI SFileCompactArchive(HANDLE hMpq, const char * szListFile, bool /* bReserved */)
{
    TFileStream * pTempStream = NULL;
    TMPQArchive * ha = (TMPQArchive *)hMpq;
    ULONGLONG ByteOffset;
    ULONGLONG ByteCount;
    LPDWORD pFileKeys = NULL;
    char szTempFile[MAX_PATH] = "";
    char * szTemp = NULL;
    int nError = ERROR_SUCCESS;

    // Test the valid parameters
    if (!IsValidMpqHandle(ha))
        nError = ERROR_INVALID_HANDLE;
    if (ha->dwFlags & MPQ_FLAG_READ_ONLY)
        nError = ERROR_ACCESS_DENIED;
    if (ha->pHetTable != NULL || ha->pBetTable != NULL)
        nError = ERROR_ACCESS_DENIED;

    // Create the table with file keys
    if (nError == ERROR_SUCCESS)
    {
        if ((pFileKeys = ALLOCMEM(DWORD, ha->dwFileTableSize)) != NULL)
            memset(pFileKeys, 0, sizeof(DWORD) * ha->dwFileTableSize);
        else
            nError = ERROR_NOT_ENOUGH_MEMORY;
    }

    // First of all, we have to check of we are able to decrypt all files.
    // If not, sorry, but the archive cannot be compacted.
    if (nError == ERROR_SUCCESS)
    {
        // Initialize the progress variables for compact callback
        FileStream_GetSize(ha->pStream, CompactTotalBytes);
        CompactBytesProcessed = 0;
        nError = CheckIfAllFilesKnown(ha, szListFile, pFileKeys);
    }

    // Get the temporary file name and create it
    if (nError == ERROR_SUCCESS)
    {
        strcpy(szTempFile, ha->pStream->szFileName);
        if ((szTemp = strrchr(szTempFile, '.')) != NULL)
            strcpy(szTemp + 1, "mp_");
        else
            strcat(szTempFile, "_");

        pTempStream = FileStream_CreateFile(szTempFile);
        if (pTempStream == NULL)
            nError = GetLastError();
    }

    // Write the data before MPQ user data (if any)
    if (nError == ERROR_SUCCESS && ha->UserDataPos != 0)
    {
        // Inform the application about the progress
        if (CompactCB != NULL)
            CompactCB(pvUserData, CCB_COPYING_NON_MPQ_DATA, CompactBytesProcessed, CompactTotalBytes);

        ByteOffset = 0;
        ByteCount = ha->UserDataPos;
        nError = CopyNonMpqData(ha->pStream, pTempStream, ByteOffset, ByteCount);
    }

    // Write the MPQ user data (if any)
    if (nError == ERROR_SUCCESS && ha->MpqPos > ha->UserDataPos)
    {
        // At this point, we assume that the user data size is equal
        // to pUserData->dwHeaderOffs.
        // If this assumption doesn't work, then we have an unknown version of MPQ
        ByteOffset = ha->UserDataPos;
        ByteCount = ha->MpqPos - ha->UserDataPos;

        assert(ha->pUserData != NULL);
        assert(ha->pUserData->dwHeaderOffs == ByteCount);
        nError = CopyNonMpqData(ha->pStream, pTempStream, ByteOffset, ByteCount);
    }

    // Write the MPQ header
    if (nError == ERROR_SUCCESS)
    {
        // Remember the header size before swapping
        DWORD dwBytesToWrite = ha->pHeader->dwHeaderSize;

        BSWAP_TMPQHEADER(ha->pHeader);
        if (!FileStream_Write(pTempStream, NULL, ha->pHeader, dwBytesToWrite))
            nError = GetLastError();
        BSWAP_TMPQHEADER(ha->pHeader);

        // Update the progress
        CompactBytesProcessed += ha->pHeader->dwHeaderSize;
        ha->dwFlags &= ~MPQ_FLAG_NO_HEADER;
    }

    // Now copy all files
    if (nError == ERROR_SUCCESS)
    {
        nError = CopyMpqFiles(ha, pFileKeys, pTempStream);
    }

    // If succeeded, switch the streams
    if (nError == ERROR_SUCCESS)
    {
        if (FileStream_MoveFile(ha->pStream, pTempStream))
            pTempStream = NULL;
        else
            nError = ERROR_CAN_NOT_COMPLETE;
    }

    // If all succeeded, save the MPQ tables
    if (nError == ERROR_SUCCESS)
    {
        //
        // Note: We don't recalculate position of the MPQ tables at this point.
        // SaveMPQTables does it automatically.
        //

        nError = SaveMPQTables(ha);
        if (nError == ERROR_SUCCESS && CompactCB != NULL)
        {
            CompactBytesProcessed += (ha->pHeader->dwHashTableSize * sizeof(TMPQHash));
            CompactBytesProcessed += (ha->pHeader->dwBlockTableSize * sizeof(TMPQBlock));
            CompactCB(pvUserData, CCB_CLOSING_ARCHIVE, CompactBytesProcessed, CompactTotalBytes);
        }
    }

    // Invalidate the compact callback
    pvUserData = NULL;
    CompactCB = NULL;

    // Cleanup and return
    if (pTempStream != NULL)
        FileStream_Close(pTempStream);
    if (pFileKeys != NULL)
        FREEMEM(pFileKeys);
    if (nError != ERROR_SUCCESS)
        SetLastError(nError);
    return (nError == ERROR_SUCCESS);
}

//-----------------------------------------------------------------------------
// Changing hash table size

bool WINAPI SFileSetHashTableSize(HANDLE hMpq, DWORD dwNewTableSize)
{
    TMPQArchive * ha = (TMPQArchive *)hMpq;
    TFileEntry * pFileTableEnd = ha->pFileTable + ha->dwFileTableSize;
    TFileEntry * pFileEntry;
    TMPQHash * pOldHashTable = NULL;
    TMPQHash * pNewHashTable = NULL;
    TMPQHash * pTableToFree = NULL;
    TMPQHash * pHash = NULL;
    DWORD dwOldHashTableSize = 0;
    int nError = ERROR_SUCCESS;

    // Test the valid parameters
    if (!IsValidMpqHandle(ha))
        nError = ERROR_INVALID_HANDLE;
    if (ha->dwFlags & MPQ_FLAG_READ_ONLY)
        nError = ERROR_ACCESS_DENIED;
    if (ha->pHetTable != NULL || ha->pHetTable != NULL)
        nError = ERROR_ACCESS_DENIED;

    // New hash table size must be a power of two
    if (dwNewTableSize & (dwNewTableSize - 1))
        nError = ERROR_INVALID_PARAMETER;

    // ALL file names must be known in order to be able
    // to rebuild hash table size
    if (nError == ERROR_SUCCESS)
        nError = CheckIfAllFilesKnown(ha, NULL, NULL);

    // Allocate buffer fo new hash table
    if (nError == ERROR_SUCCESS)
    {
        dwOldHashTableSize = ha->pHeader->dwHashTableSize;
        pOldHashTable = ha->pHashTable;

        pNewHashTable = ALLOCMEM(TMPQHash, dwNewTableSize);
        if (pOldHashTable == NULL || pNewHashTable == NULL)
            nError = ERROR_NOT_ENOUGH_MEMORY;
    }

    // Now build the new hash table
    // we have to reallocate block table, and also all tables in the (attributes)
    if (nError == ERROR_SUCCESS)
    {
        // Set new hash table
        memset(pNewHashTable, 0xFF, dwNewTableSize * sizeof(TMPQHash));
        ha->pHashTable = pNewHashTable;
        ha->pHeader->dwHashTableSize = dwNewTableSize;

        // Make new hash table entry for each file
        for (pFileEntry = ha->pFileTable; pFileEntry < pFileTableEnd; pFileEntry++)
        {
            if (pFileEntry->dwFlags & MPQ_FILE_EXISTS)
            {
                // The file name must be known
                assert(pFileEntry->szFileName != NULL);

                // Create new hashtable entry
                pHash = AllocateHashEntry(ha, pFileEntry->szFileName, pFileEntry->lcLocale);
                if (pHash == NULL)
                {
                    nError = ERROR_CAN_NOT_COMPLETE;
                    break;
                }

                // Fill the hash table entry
                pHash->wPlatform = pFileEntry->wPlatform;
                pHash->dwBlockIndex = (DWORD)(pFileEntry - ha->pFileTable);

                // Fix the hash table index
                pFileEntry->dwHashIndex = (DWORD)(pHash - pNewHashTable);
            }
        }

        // If something failed, we have to revert hash table
        if (nError == ERROR_SUCCESS)
        {
            pTableToFree = pOldHashTable;
            ha->dwFlags |= MPQ_FLAG_CHANGED;
        }
        else
        {
            ha->pHeader->dwHashTableSize = dwOldHashTableSize;
            ha->pHashTable = pOldHashTable;
            pTableToFree = pNewHashTable;
        }
    }

    // Free buffers
    if (pTableToFree != NULL)
        FREEMEM(pTableToFree);

    // Return the result
    if (nError != ERROR_SUCCESS)
        SetLastError(nError);
    return (nError == ERROR_SUCCESS);
}