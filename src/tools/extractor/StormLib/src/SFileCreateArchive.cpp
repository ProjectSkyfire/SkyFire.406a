/*****************************************************************************/
/* SFileCreateArchive.cpp                 Copyright (c) Ladislav Zezula 2003 */
/*---------------------------------------------------------------------------*/
/* MPQ Editing functions                                                     */
/*---------------------------------------------------------------------------*/
/*   Date    Ver   Who  Comment                                              */
/* --------  ----  ---  -------                                              */
/* 24.03.03  1.00  Lad  Splitted from SFileOpenArchive.cpp                   */
/* 08.06.10  1.00  Lad  Renamed to SFileCreateArchive.cpp                    */
/*****************************************************************************/

#define __STORMLIB_SELF__
#include "StormLib.h"
#include "StormCommon.h"

//-----------------------------------------------------------------------------
// Defines

#define DEFAULT_SECTOR_SIZE  3       // Default size of a file sector

//-----------------------------------------------------------------------------
// Local variables

static const DWORD MpqHeaderSizes[] =
{
    MPQ_HEADER_SIZE_V1,
    MPQ_HEADER_SIZE_V2,
    MPQ_HEADER_SIZE_V3,
    MPQ_HEADER_SIZE_V4
};

//-----------------------------------------------------------------------------
// Creates a new MPQ archive.

bool WINAPI SFileCreateArchive(const char * szMpqName, DWORD dwFlags, DWORD dwHashTableSize, HANDLE * phMpq)
{
    TFileStream * pStream = NULL;           // File stream
    TMPQArchive * ha = NULL;                // MPQ archive handle
    ULONGLONG MpqPos = 0;                   // Position of MPQ header in the file
    USHORT wFormatVersion = MPQ_FORMAT_VERSION_1;
    DWORD dwBlockTableSize = 0;             // Initial block table size
    DWORD dwPowerOfTwo;
    int nError = ERROR_SUCCESS;

    // Check the parameters, if they are valid
    if (szMpqName == NULL || *szMpqName == 0 || phMpq == NULL)
    {
        SetLastError(ERROR_INVALID_PARAMETER);
        return false;
    }

    // One time initialization of MPQ cryptography
    InitializeMpqCryptography();

    // We verify if the file already exists and if it's a MPQ archive.
    // If yes, we won't allow to overwrite it.
    if (!(dwFlags & MPQ_CREATE_NO_MPQ_CHECK))
    {
        HANDLE hMpq = NULL;

        if (SFileOpenArchive(szMpqName, 0, dwFlags, &hMpq))
        {
            SFileCloseArchive(hMpq);
            SetLastError(ERROR_ALREADY_EXISTS);
            return false;
        }
    }

    //
    // At this point, we have to create the archive.
    // - If the file exists, convert it to MPQ archive.
    // - If the file doesn't exist, create new empty file
    //

    pStream = FileStream_OpenFile(szMpqName, true);
    if (pStream == NULL)
    {
        pStream = FileStream_CreateFile(szMpqName);
        if (pStream == NULL)
            return false;
    }

    // Decide what format to use
    wFormatVersion = (USHORT)((dwFlags & MPQ_CREATE_ARCHIVE_VMASK) >> 16);

    // Retrieve the file size and round it up to 0x200 bytes
    FileStream_GetSize(pStream, MpqPos);
    MpqPos = (MpqPos + 0x1FF) & (ULONGLONG)0xFFFFFFFFFFFFFE00ULL;
    if (!FileStream_SetSize(pStream, MpqPos))
        nError = GetLastError();

    // Create the archive handle
    if (nError == ERROR_SUCCESS)
    {
        if ((ha = ALLOCMEM(TMPQArchive, 1)) == NULL)
            nError = ERROR_NOT_ENOUGH_MEMORY;
    }

    // Fill the MPQ archive handle structure and create the header,
    // hash table and block table
    if (nError == ERROR_SUCCESS)
    {
        // Round the hash table size up to the nearest power of two
        for(dwPowerOfTwo = HASH_TABLE_SIZE_MIN; dwPowerOfTwo < HASH_TABLE_SIZE_MAX; dwPowerOfTwo <<= 1)
        {
            if (dwPowerOfTwo >= dwHashTableSize)
            {
                dwHashTableSize = dwPowerOfTwo;
                break;
            }
        }

        // Don't allow the hash table size go over allowed maximum
        dwHashTableSize = STORMLIB_MIN(dwHashTableSize, HASH_TABLE_SIZE_MAX);

#ifdef _DEBUG
        // Debug code, used for testing StormLib
//      dwBlockTableSize = dwHashTableSize * 2;
#endif

        memset(ha, 0, sizeof(TMPQArchive));
        ha->pStream         = pStream;
        ha->dwSectorSize    = 0x200 << DEFAULT_SECTOR_SIZE;
        ha->UserDataPos     = MpqPos;
        ha->MpqPos          = MpqPos;
        ha->pHeader         = (TMPQHeader *)ha->HeaderData;
        ha->dwFileTableSize = 0;
        ha->dwFileTableMax  = dwHashTableSize;
        ha->dwFlags         = 0;
        pStream = NULL;

        // Setup the attributes
        if (dwFlags & MPQ_CREATE_ATTRIBUTES)
            ha->dwAttrFlags = MPQ_ATTRIBUTE_CRC32 | MPQ_ATTRIBUTE_FILETIME | MPQ_ATTRIBUTE_MD5;

        // Create hash table and file tablt
        ha->pHashTable = ALLOCMEM(TMPQHash, dwHashTableSize);
        ha->pFileTable = ALLOCMEM(TFileEntry, ha->dwFileTableMax);
        if (!ha->pHashTable || !ha->pFileTable)
            nError = ERROR_NOT_ENOUGH_MEMORY;
    }

    // Fill the MPQ header and all buffers
    if (nError == ERROR_SUCCESS)
    {
        TMPQHeader * pHeader = ha->pHeader;

        // Fill the MPQ header
        memset(pHeader, 0, sizeof(ha->HeaderData));
        pHeader->dwID             = ID_MPQ;
        pHeader->dwHeaderSize     = MpqHeaderSizes[wFormatVersion];
        pHeader->dwArchiveSize    = pHeader->dwHeaderSize + dwHashTableSize * sizeof(TMPQHash);
        pHeader->wFormatVersion   = wFormatVersion;
        pHeader->wSectorSize      = DEFAULT_SECTOR_SIZE; // 0x1000 bytes per sector
        pHeader->dwHashTablePos   = pHeader->dwHeaderSize;
        pHeader->dwHashTableSize  = dwHashTableSize;
        pHeader->dwBlockTablePos  = pHeader->dwHashTablePos + dwHashTableSize * sizeof(TMPQHash);
        pHeader->dwBlockTableSize = dwBlockTableSize;
        ConvertMpqHeaderToFormat4(ha, MpqPos, 0);

        // Clear all tables
        memset(ha->pHashTable, 0xFF, sizeof(TMPQHash) * dwHashTableSize);
        memset(ha->pFileTable, 0x00, sizeof(TFileEntry) * ha->dwFileTableMax);

        // Remember if we shall check sector CRCs when reading file
        if (dwFlags & MPQ_OPEN_CHECK_SECTOR_CRC)
            ha->dwFlags |= MPQ_FLAG_CHECK_SECTOR_CRC;

        //
        // Note: Don't write the MPQ header at this point. If any operation fails later,
        // the unfinished MPQ would stay on the disk, being 0x20 (or 0x2C) bytes long,
        // containing naked MPQ header.
        //

        ha->dwFlags |= MPQ_FLAG_NO_HEADER;

        //
        // Note: Don't recalculate position of MPQ tables at this point.
        // We merely set a flag that indicates that the MPQ tables
        // have been changed, and SaveMpqTables will do the work when closing the archive.
        //

        ha->dwFlags |= MPQ_FLAG_CHANGED;
    }

    // Cleanup : If an error, delete all buffers and return
    if (nError != ERROR_SUCCESS)
    {
        FileStream_Close(pStream);
        FreeMPQArchive(ha);
        SetLastError(nError);
        ha = NULL;
    }

    // Return the values
    *phMpq = (HANDLE)ha;
    return (nError == ERROR_SUCCESS);
}