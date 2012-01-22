/*****************************************************************************/
/* SBaseCommon.cpp                        Copyright (c) Ladislav Zezula 2003 */
/*---------------------------------------------------------------------------*/
/* Common functions for StormLib, used by all SFile*** modules               */
/*---------------------------------------------------------------------------*/
/*   Date    Ver   Who  Comment                                              */
/* --------  ----  ---  -------                                              */
/* 24.03.03  1.00  Lad  The first version of SFileCommon.cpp                 */
/* 19.11.03  1.01  Dan  Big endian handling                                  */
/* 12.06.04  1.01  Lad  Renamed to SCommon.cpp                               */
/* 06.09.10  1.01  Lad  Renamed to SBaseCommon.cpp                           */
/*****************************************************************************/

#define __STORMLIB_SELF__
#define __INCLUDE_CRYPTOGRAPHY__
#include "StormLib.h"
#include "StormCommon.h"

char StormLibCopyright[] = "StormLib v " STORMLIB_VERSION_STRING " Copyright Ladislav Zezula 1998-2010";

//-----------------------------------------------------------------------------
// The buffer for decryption engine.

LCID    lcFileLocale = LANG_NEUTRAL;            // File locale
USHORT  wPlatform = 0;                          // File platform

//-----------------------------------------------------------------------------
// Storm buffer functions

#define MPQ_HASH_TABLE_OFFSET   0x000
#define MPQ_HASH_NAME_A         0x100
#define MPQ_HASH_NAME_B         0x200
#define MPQ_HASH_FILE_KEY       0x300

#define STORM_BUFFER_SIZE       0x500

static DWORD StormBuffer[STORM_BUFFER_SIZE];    // Buffer for the decryption engine
static bool  bMpqCryptographyInitialized = false;

static DWORD HashString(const char * szFileName, DWORD dwHashType)
{
    LPBYTE pbKey   = (BYTE *)szFileName;
    DWORD  dwSeed1 = 0x7FED7FED;
    DWORD  dwSeed2 = 0xEEEEEEEE;
    DWORD  ch;

    while (*pbKey != 0)
    {
        ch = toupper(*pbKey++);

        dwSeed1 = StormBuffer[dwHashType + ch] ^ (dwSeed1 + dwSeed2);
        dwSeed2 = ch + dwSeed1 + dwSeed2 + (dwSeed2 << 5) + 3;
    }

    return dwSeed1;
}

void InitializeMpqCryptography()
{
    DWORD dwSeed = 0x00100001;
    DWORD index1 = 0;
    DWORD index2 = 0;
    int   i;

    // Initialize the decryption buffer.
    // Do nothing if already done.
    if (bMpqCryptographyInitialized == false)
    {
        for (index1 = 0; index1 < 0x100; index1++)
        {
            for (index2 = index1, i = 0; i < 5; i++, index2 += 0x100)
            {
                DWORD temp1, temp2;

                dwSeed = (dwSeed * 125 + 3) % 0x2AAAAB;
                temp1  = (dwSeed & 0xFFFF) << 0x10;

                dwSeed = (dwSeed * 125 + 3) % 0x2AAAAB;
                temp2  = (dwSeed & 0xFFFF);

                StormBuffer[index2] = (temp1 | temp2);
            }
        }

        // Also register both MD5 and SHA1 hash algorithms
        register_hash(&md5_desc);
        register_hash(&sha1_desc);

        // Use LibTomMath as support math library for LibTomCrypt
        ltc_mp = ltm_desc;

        // Don't do that again
        bMpqCryptographyInitialized = true;
    }
}

//-----------------------------------------------------------------------------
// Verifies if the file name is a pseudo-name

bool IsPseudoFileName(const char * szFileName, DWORD * pdwFileIndex)
{
    const char * szExt = strrchr(szFileName, '.');

    // Must have an extension
    if (szExt != NULL)
    {
        // Length of the name part must be 12 characters
        if ((szExt - szFileName) == 12)
        {
            // Must begin with "File"
            if (!_strnicmp(szFileName, "File", 4))
            {
                // Must be 8 digits after "File"
                if (isdigit(szFileName[4]) && isdigit(szFileName[11]))
                {
                    if (pdwFileIndex != NULL)
                        *pdwFileIndex = strtol(szFileName + 4, (char **)&szExt, 10);
                    return true;
                }
            }
        }
    }

    return false;
}

//-----------------------------------------------------------------------------
// Calculates a Jenkin's Encrypting and decrypting MPQ file data

ULONGLONG HashStringJenkins(const char * szFileName)
{
    char * szTemp;
    char szLocFileName[0x108];
    char chOneChar;
    size_t nLength = 0;
    unsigned int primary_hash = 1;
    unsigned int secondary_hash = 2;

    // This is required to produce defined results
    assert(szFileName != NULL);

    // Normalize the file name - convert to uppercase, and convert "/" to "\\".
    if (szFileName != NULL)
    {
        szTemp = szLocFileName;
        while (*szFileName != 0)
        {
            chOneChar = (char)tolower(*szFileName++);
            if (chOneChar == '/')
                chOneChar = '\\';

            *szTemp++ = chOneChar;
        }

        nLength = szTemp - szLocFileName;
        *szTemp = 0;
    }

    // Thanks Quantam for finding out what the algorithm is.
    // I am really getting old for reversing large chunks of assembly
    // that does hashing :-)
    hashlittle2(szLocFileName, nLength, &secondary_hash, &primary_hash);

    // Combine those 2 together
    return (ULONGLONG)primary_hash * (ULONGLONG)0x100000000ULL + (ULONGLONG)secondary_hash;
}

//-----------------------------------------------------------------------------
// This function converts the MPQ header so it always looks like version 4

void ConvertMpqHeaderToFormat4(
    TMPQArchive * ha,
    ULONGLONG FileSize,
    DWORD dwFlags)
{
    ULONGLONG ByteOffset;
    TMPQHeader * pHeader = ha->pHeader;
    DWORD dwExpectedArchiveSize;
    USHORT wFormatVersion = pHeader->wFormatVersion;

    // If version 1.0 is forced, then the format version is forced to be 1.0
    // Reason: Storm.dll in Warcraft III ignores format version value
    if (dwFlags & MPQ_OPEN_FORCE_MPQ_V1)
        wFormatVersion = MPQ_FORMAT_VERSION_1;

    // Format-specific fixes
    switch (wFormatVersion)
    {
        case MPQ_FORMAT_VERSION_1:

            // Check for malformed MPQ header version 1.0
            if (pHeader->dwHeaderSize != MPQ_HEADER_SIZE_V1)
            {
                pHeader->dwHeaderSize = MPQ_HEADER_SIZE_V1;
                ha->dwFlags |= MPQ_FLAG_PROTECTED;
            }

            //
            // The value of "dwArchiveSize" member in the MPQ header
            // is ignored by Storm.dll and can contain garbage value
            // ("w3xmaster" protector).
            //

            dwExpectedArchiveSize = (DWORD)(FileSize - ha->MpqPos);
            if (pHeader->dwArchiveSize != dwExpectedArchiveSize)
            {
                // Note: dwExpectedArchiveSize might be incorrect at this point.
                // MPQs version 1.0 can have strong digital signature appended at the end,
                // or they might just have arbitrary data there.
                // In either case, we recalculate the archive size later when
                // block table is loaded and positions of all files is known.
                pHeader->dwArchiveSize = dwExpectedArchiveSize;
                ha->dwFlags |= MPQ_FLAG_NEED_FIX_SIZE;
            }

            // Zero the fields in 2.0 part of the MPQ header
            pHeader->HiBlockTablePos64 = 0;
            pHeader->wHashTablePosHi = 0;
            pHeader->wBlockTablePosHi = 0;
            // No break here !!!

        case MPQ_FORMAT_VERSION_2:
        case MPQ_FORMAT_VERSION_3:

            // In MPQ format 3.0, the entire header is optional
            // and the size of the header can actually be identical
            // to size of header 2.0
            if (pHeader->dwHeaderSize < MPQ_HEADER_SIZE_V3)
            {
                ULONGLONG ArchiveSize64 = pHeader->dwArchiveSize;

                // In format 2.0, the archive size is obsolete and is calculated
                // as the highest offset of hash table, block table or hi-block table.
                // However, we can still rely on it, if the size of the archive is under 4 GB
                if ((FileSize - ha->MpqPos) >> 32)
                {
                    ByteOffset = MAKE_OFFSET64(pHeader->wHashTablePosHi, pHeader->dwHashTablePos) + (pHeader->dwHashTableSize * sizeof(TMPQHash));
                    if (ByteOffset > ArchiveSize64)
                        ArchiveSize64 = ByteOffset;

                    ByteOffset = MAKE_OFFSET64(pHeader->wBlockTablePosHi, pHeader->dwBlockTablePos) + (pHeader->dwBlockTableSize * sizeof(TMPQBlock));
                    if (ByteOffset > ArchiveSize64)
                        ArchiveSize64 = ByteOffset;

                    // Only if we actually have a hi-block table
                    if (pHeader->HiBlockTablePos64)
                    {
                        ByteOffset = pHeader->HiBlockTablePos64 + (pHeader->dwBlockTableSize * sizeof(USHORT));
                        if (ByteOffset > ArchiveSize64)
                            ArchiveSize64 = ByteOffset;
                    }

                    // We need to recalculate archive size later,
                    // when block table is loaded and the position of files is known
                    ha->dwFlags |= MPQ_FLAG_NEED_FIX_SIZE;
                }

                // Initialize the rest of the 3.0 header
                pHeader->ArchiveSize64 = ArchiveSize64;
                pHeader->HetTablePos64 = 0;
                pHeader->BetTablePos64 = 0;
            }

            //
            // Calculate compressed size of each table. We assume the following order:
            // 1) HET table
            // 2) BET table
            // 3) Classic hash table
            // 4) Classic block table
            // 5) Hi-block table
            //

            // Set all sizes to zero
            pHeader->HetTableSize64 = 0;
            pHeader->BetTableSize64 = 0;

            // Either both HET and BET table exist or none of them does.
            if (pHeader->HetTablePos64)
            {
                // Compressed size of the HET and BET tables
                pHeader->HetTableSize64 = pHeader->BetTablePos64 - pHeader->HetTablePos64;
                pHeader->BetTableSize64 = MAKE_OFFSET64(pHeader->wHashTablePosHi, pHeader->dwHashTablePos) - pHeader->HetTablePos64;
            }

            // Compressed size of hash and block table
            if (wFormatVersion >= MPQ_FORMAT_VERSION_3)
            {
                // Compressed size of the hash table
                pHeader->HashTableSize64 = MAKE_OFFSET64(pHeader->wBlockTablePosHi, pHeader->dwBlockTablePos) - MAKE_OFFSET64(pHeader->wHashTablePosHi, pHeader->dwHashTablePos);

                // Block and hi-block table
                if (pHeader->HiBlockTablePos64)
                {
                    pHeader->BlockTableSize64 = pHeader->HiBlockTablePos64 - MAKE_OFFSET64(pHeader->wBlockTablePosHi, pHeader->dwBlockTablePos);
                    pHeader->HiBlockTableSize64 = pHeader->ArchiveSize64 - pHeader->HiBlockTablePos64;
                }
                else
                {
                    pHeader->BlockTableSize64 = pHeader->ArchiveSize64 - MAKE_OFFSET64(pHeader->wBlockTablePosHi, pHeader->dwBlockTablePos);
                    pHeader->HiBlockTableSize64 = 0;
                }
            }
            else
            {
                // No known MPQ in format 1.0 has any of the tables compressed
                pHeader->HashTableSize64 = pHeader->dwHashTableSize * sizeof(TMPQHash);
                pHeader->BlockTableSize64 = pHeader->dwBlockTableSize * sizeof(TMPQBlock);
                pHeader->HiBlockTableSize64 = 0;
            }

            // Set the data chunk size for MD5 to zero
            pHeader->dwRawChunkSize = 0;

            // Fill the MD5's
            memset(pHeader->MD5_BlockTable,  0, MD5_DIGEST_SIZE);
            memset(pHeader->MD5_HashTable,   0, MD5_DIGEST_SIZE);
            memset(pHeader->MD5_HiBlockTable, 0, MD5_DIGEST_SIZE);
            memset(pHeader->MD5_UnknownA0,   0, MD5_DIGEST_SIZE);
            memset(pHeader->MD5_UnknownB0,   0, MD5_DIGEST_SIZE);
            memset(pHeader->MD5_MpqHeader,   0, MD5_DIGEST_SIZE);
            // No break here !!!!

        case MPQ_FORMAT_VERSION_4:

            // Verify header MD5. Header MD5 is calculated from the MPQ header since the 'MPQ\x1A'
            // signature until the position of header MD5 at offset 0xC0
//          if (dwHeaderSize >= MPQ_HEADER_SIZE_V4)
//              wow_SFileVerifyMpqHeaderMD5(ha->pHeader);
            break;
    }
}

//-----------------------------------------------------------------------------
// Encrypting and decrypting MPQ file data

void EncryptMpqBlock(void * pvFileBlock, DWORD dwLength, DWORD dwSeed1)
{
    LPDWORD block = (LPDWORD)pvFileBlock;
    DWORD dwSeed2 = 0xEEEEEEEE;
    DWORD ch;

    // Round to DWORDs
    dwLength >>= 2;

    while (dwLength-- > 0)
    {
        dwSeed2 += StormBuffer[0x400 + (dwSeed1 & 0xFF)];
        ch     = *block;
        *block++ = ch ^ (dwSeed1 + dwSeed2);

        dwSeed1  = ((~dwSeed1 << 0x15) + 0x11111111) | (dwSeed1 >> 0x0B);
        dwSeed2  = ch + dwSeed2 + (dwSeed2 << 5) + 3;
    }
}

void DecryptMpqBlock(void * pvFileBlock, DWORD dwLength, DWORD dwSeed1)
{
    LPDWORD block = (LPDWORD)pvFileBlock;
    DWORD dwSeed2 = 0xEEEEEEEE;
    DWORD ch;

    // Round to DWORDs
    dwLength >>= 2;

    while (dwLength-- > 0)
    {
        dwSeed2 += StormBuffer[0x400 + (dwSeed1 & 0xFF)];
        ch     = *block ^ (dwSeed1 + dwSeed2);

        dwSeed1  = ((~dwSeed1 << 0x15) + 0x11111111) | (dwSeed1 >> 0x0B);
        dwSeed2  = ch + dwSeed2 + (dwSeed2 << 5) + 3;
        *block++ = ch;
    }
}

/*
void EncryptMpqTable(void * pvMpqTable, DWORD dwLength, const char * szKey)
{
    EncryptMpqBlock(pvMpqTable, dwLength, HashString(szKey, MPQ_HASH_FILE_KEY));
}

void DecryptMpqTable(void * pvMpqTable, DWORD dwLength, const char * szKey)
{
    DecryptMpqBlock(pvMpqTable, dwLength, HashString(szKey, MPQ_HASH_FILE_KEY));
}
*/
//-----------------------------------------------------------------------------
// Functions tries to get file decryption key. The trick comes from sector
// positions which are stored at the begin of each compressed file. We know the
// file size, that means we know number of sectors that means we know the first
// DWORD value in sector position. And if we know encrypted and decrypted value,
// we can find the decryption key !!!
//
// hf            - MPQ file handle
// SectorOffsets - DWORD array of sector positions
// ch            - Decrypted value of the first sector pos

DWORD DetectFileKeyBySectorSize(LPDWORD SectorOffsets, DWORD decrypted)
{
    DWORD saveKey1;
    DWORD temp = *SectorOffsets ^ decrypted;    // temp = seed1 + seed2
    temp -= 0xEEEEEEEE;                 // temp = seed1 + StormBuffer[0x400 + (seed1 & 0xFF)]

    for (int i = 0; i < 0x100; i++)      // Try all 255 possibilities
    {
        DWORD seed1;
        DWORD seed2 = 0xEEEEEEEE;
        DWORD ch;

        // Try the first DWORD (We exactly know the value)
        seed1  = temp - StormBuffer[0x400 + i];
        seed2 += StormBuffer[0x400 + (seed1 & 0xFF)];
        ch     = SectorOffsets[0] ^ (seed1 + seed2);

        if (ch != decrypted)
            continue;

        // Add 1 because we are decrypting sector positions
        saveKey1 = seed1 + 1;

        // If OK, continue and test the second value. We don't know exactly the value,
        // but we know that the second one has lower 16 bits set to zero
        // (no compressed sector is larger than 0xFFFF bytes)
        seed1  = ((~seed1 << 0x15) + 0x11111111) | (seed1 >> 0x0B);
        seed2  = ch + seed2 + (seed2 << 5) + 3;

        seed2 += StormBuffer[0x400 + (seed1 & 0xFF)];
        ch     = SectorOffsets[1] ^ (seed1 + seed2);

        if ((ch & 0xFFFF0000) == 0)
            return saveKey1;
    }
    return 0;
}

// Function tries to detect file encryption key. It expectes at least two uncompressed bytes
DWORD DetectFileKeyByKnownContent(void * pvFileContent, DWORD nDwords, ...)
{
    LPDWORD pdwContent = (LPDWORD)pvFileContent;
    va_list argList;
    DWORD dwDecrypted[0x10];
    DWORD saveKey1;
    DWORD dwTemp;
    DWORD i, j;

    // We need at least two DWORDS to detect the file key
    if (nDwords < 0x02 || nDwords > 0x10)
        return 0;

    va_start(argList, nDwords);
    for (i = 0; i < nDwords; i++)
        dwDecrypted[i] = va_arg(argList, DWORD);
    va_end(argList);

    dwTemp = (*pdwContent ^ dwDecrypted[0]) - 0xEEEEEEEE;
    for (i = 0; i < 0x100; i++)      // Try all 256 possibilities
    {
        DWORD seed1;
        DWORD seed2 = 0xEEEEEEEE;
        DWORD ch;

        // Try the first DWORD
        seed1  = dwTemp - StormBuffer[0x400 + i];
        seed2 += StormBuffer[0x400 + (seed1 & 0xFF)];
        ch     = pdwContent[0] ^ (seed1 + seed2);

        if (ch != dwDecrypted[0])
            continue;

        saveKey1 = seed1;

        // If OK, continue and test all bytes.
        for (j = 1; j < nDwords; j++)
        {
            seed1  = ((~seed1 << 0x15) + 0x11111111) | (seed1 >> 0x0B);
            seed2  = ch + seed2 + (seed2 << 5) + 3;

            seed2 += StormBuffer[0x400 + (seed1 & 0xFF)];
            ch     = pdwContent[j] ^ (seed1 + seed2);

            if (ch == dwDecrypted[j] && j == nDwords - 1)
                return saveKey1;
        }
    }
    return 0;
}

DWORD DetectFileKeyByContent(void * pvFileContent, DWORD dwFileSize)
{
    DWORD dwFileKey;

    // Try to break the file encryption key as if it was a WAVE file
    if (dwFileSize >= 0x0C)
    {
        dwFileKey = DetectFileKeyByKnownContent(pvFileContent, 3, 0x46464952, dwFileSize - 8, 0x45564157);
        if (dwFileKey != 0)
            return dwFileKey;
    }

    // Try to break the encryption key as if it was an EXE file
    if (dwFileSize > 0x40)
    {
        dwFileKey = DetectFileKeyByKnownContent(pvFileContent, 2, 0x00905A4D, 0x00000003);
        if (dwFileKey != 0)
            return dwFileKey;
    }

    // Try to break the encryption key as if it was a XML file
    if (dwFileSize > 0x04)
    {
        dwFileKey = DetectFileKeyByKnownContent(pvFileContent, 2, 0x6D783F3C, 0x6576206C);
        if (dwFileKey != 0)
            return dwFileKey;
    }

    // Not detected, sorry
    return 0;
}

DWORD DecryptFileKey(
    const char * szFileName,
    ULONGLONG MpqPos,
    DWORD dwFileSize,
    DWORD dwFlags)
{
    DWORD dwFileKey;
    DWORD dwMpqPos = (DWORD)MpqPos;

    // File key is calculated from plain name
    szFileName = GetPlainFileName(szFileName);
    dwFileKey = HashString(szFileName, MPQ_HASH_FILE_KEY);

    // Fix the key, if needed
    if (dwFlags & MPQ_FILE_FIX_KEY)
        dwFileKey = (dwFileKey + dwMpqPos) ^ dwFileSize;

    // Return the key
    return dwFileKey;
}

//-----------------------------------------------------------------------------
// Handle validation functions

bool IsValidMpqHandle(TMPQArchive * ha)
{
    if (ha == NULL)
        return false;
    if (ha->pHeader == NULL || ha->pHeader->dwID != ID_MPQ)
        return false;

    return (bool)(ha->pHeader->dwID == ID_MPQ);
}

bool IsValidFileHandle(TMPQFile * hf)
{
    if (hf == NULL)
        return false;

    if (hf->dwMagic != ID_MPQ_FILE)
        return false;

    if (hf->pStream != NULL)
        return true;

    return IsValidMpqHandle(hf->ha);
}

//-----------------------------------------------------------------------------
// Hash table and block table manipulation

// Retrieves the first hash entry for the given file.
// Every locale version of a file has its own hash entry
TMPQHash * GetFirstHashEntry(TMPQArchive * ha, const char * szFileName)
{
    TMPQHash * pStartHash;                  // File hash entry (start)
    TMPQHash * pHashEnd = ha->pHashTable + ha->pHeader->dwHashTableSize;
    TMPQHash * pHash;                       // File hash entry (current)
    DWORD dwHashTableSizeMask;
    DWORD dwIndex = HashString(szFileName, MPQ_HASH_TABLE_OFFSET);
    DWORD dwName1 = HashString(szFileName, MPQ_HASH_NAME_A);
    DWORD dwName2 = HashString(szFileName, MPQ_HASH_NAME_B);

    // Get the first possible has entry that might be the one
    dwHashTableSizeMask = ha->pHeader->dwHashTableSize ? (ha->pHeader->dwHashTableSize - 1) : 0;
    pStartHash = pHash = ha->pHashTable + (dwIndex & dwHashTableSizeMask);

    // There might be deleted entries in the hash table prior to our desired entry.
    while (pHash->dwBlockIndex != HASH_ENTRY_FREE)
    {
        // If the entry agrees, we found it.
        if (pHash->dwName1 == dwName1 && pHash->dwName2 == dwName2 && pHash->dwBlockIndex < ha->dwFileTableSize)
            return pHash;

        // Move to the next hash entry. Stop searching
        // if we got reached the original hash entry
        if (++pHash >= pHashEnd)
            pHash = ha->pHashTable;
        if (pHash == pStartHash)
            break;
    }

    // The apropriate hash entry was not found
    return NULL;
}

TMPQHash * GetNextHashEntry(TMPQArchive * ha, TMPQHash * pFirstHash, TMPQHash * pPrevHash)
{
    TMPQHash * pHashEnd = ha->pHashTable + ha->pHeader->dwHashTableSize;
    TMPQHash * pHash = pPrevHash;
    DWORD dwName1 = pPrevHash->dwName1;
    DWORD dwName2 = pPrevHash->dwName2;

    // Now go for any next entry that follows the pPrevHash,
    // until either free hash entry was found, or the start entry was reached
    for (;;)
    {
        // Move to the next hash entry. Stop searching
        // if we got reached the original hash entry
        if (++pHash >= pHashEnd)
            pHash = ha->pHashTable;
        if (pHash == pFirstHash)
            break;

        // If the entry is a free entry, stop search
        if (pHash->dwBlockIndex == HASH_ENTRY_FREE)
            break;

        // If the entry is not free and the name agrees, we found it
        if (pHash->dwName1 == dwName1 && pHash->dwName2 == dwName2 && pHash->dwBlockIndex < ha->pHeader->dwBlockTableSize)
            return pHash;
    }

    // No next entry
    return NULL;
}

// Allocates an entry in the hash table
TMPQHash * AllocateHashEntry(TMPQArchive * ha, const char * szFileName, LCID lcLocale)
{
    TMPQHash * pStartHash;                  // File hash entry (start)
    TMPQHash * pHashEnd = ha->pHashTable + ha->pHeader->dwHashTableSize;
    TMPQHash * pHash;                       // File hash entry (current)
    DWORD dwHashTableSizeMask;
    DWORD dwIndex = HashString(szFileName, MPQ_HASH_TABLE_OFFSET);
    DWORD dwName1 = HashString(szFileName, MPQ_HASH_NAME_A);
    DWORD dwName2 = HashString(szFileName, MPQ_HASH_NAME_B);

    // Get the first possible has entry that might be the one
    dwHashTableSizeMask = ha->pHeader->dwHashTableSize ? (ha->pHeader->dwHashTableSize - 1) : 0;
    pStartHash = pHash = ha->pHashTable + (dwIndex & dwHashTableSizeMask);

    // There might be deleted entries in the hash table prior to our desired entry.
    while (pHash->dwBlockIndex < HASH_ENTRY_DELETED)
    {
        // If there already is an existing entry, reuse it.
        if (pHash->dwName1 == dwName1 && pHash->dwName2 == dwName2 && pHash->lcLocale == lcLocale)
            return pHash;

        // Move to the next hash entry.
        // If we reached the starting entry, it's failure.
        if (++pHash >= pHashEnd)
            pHash = ha->pHashTable;
        if (pHash == pStartHash)
            return NULL;
    }

    // Take the next free hash table entry
    assert(pHash->dwBlockIndex >= HASH_ENTRY_DELETED);
    pHash->dwName1  = dwName1;
    pHash->dwName2  = dwName2;
    pHash->lcLocale = (USHORT)lcLocale;
    pHash->wPlatform = 0;
    return pHash;
}

// Finds a free space in the MPQ where to store next data
// The free space begins beyond the file that is stored at the fuhrtest
// position in the MPQ.
void FindFreeMpqSpace(TMPQArchive * ha, ULONGLONG * pMpqPos)
{
    TFileEntry * pFileTableEnd = ha->pFileTable + ha->dwFileTableSize;
    TFileEntry * pFileEntry = ha->pFileTable;
    ULONGLONG MpqPos = ha->pHeader->dwHeaderSize;

    // Parse the entire block table
    while (pFileEntry < pFileTableEnd)
    {
        // Only take existing files
        if (pFileEntry->dwFlags & MPQ_FILE_EXISTS)
        {
            // If the end of the file is bigger than current MPQ table pos, update it
            if ((pFileEntry->ByteOffset + pFileEntry->dwCmpSize) > MpqPos)
                MpqPos = pFileEntry->ByteOffset + pFileEntry->dwCmpSize;
        }

        // Move to the next file entry
        pFileEntry++;
    }

    // Give the free space position to the caller
    if (pMpqPos != NULL)
        *pMpqPos = MpqPos;
}

//-----------------------------------------------------------------------------
// Common functions - MPQ File

TMPQFile * CreateMpqFile(TMPQArchive * ha)
{
    TMPQFile * hf;

    // Allocate space for TMPQFile
    hf = ALLOCMEM(TMPQFile, 1);
    if (hf != NULL)
    {
        // Fill the file structure
        memset(hf, 0, sizeof(TMPQFile));
        hf->ha = ha;
        hf->pStream = NULL;
        hf->dwMagic = ID_MPQ_FILE;
    }

    return hf;
}

// Loads a table from MPQ.
// Can be used for hash table, block table, sector offset table or sector checksum table
int LoadMpqTable(
    TMPQArchive * ha,
    ULONGLONG ByteOffset,
    void * pvTable,
    DWORD dwCompressedSize,
    DWORD dwRealSize,
    DWORD dwKey)
{
    ULONGLONG ByteOffsetLi;
    LPBYTE pbCompressed = NULL;
    LPBYTE pbToRead = (LPBYTE)pvTable;
    int nError = ERROR_SUCCESS;

    // Is the table compressed ?
    if (dwCompressedSize < dwRealSize)
    {
        // Allocate temporary buffer for holding compressed data
        pbCompressed = ALLOCMEM(BYTE, dwCompressedSize);
        if (pbCompressed == NULL)
            return ERROR_NOT_ENOUGH_MEMORY;

        // Assign the temporary buffer as target for read operation
        pbToRead = pbCompressed;
    }

    // Read the table
    ByteOffsetLi = ByteOffset;
    if (FileStream_Read(ha->pStream, &ByteOffsetLi, pbToRead, dwCompressedSize))
    {
        // First of all, decrypt the table
        if (dwKey != 0)
        {
            BSWAP_ARRAY32_UNSIGNED(pbToRead, dwCompressedSize);
            DecryptMpqBlock(pbToRead, dwCompressedSize, dwKey);
            BSWAP_ARRAY32_UNSIGNED(pbToRead, dwCompressedSize);
        }

        // If the table is compressed, decompress it
        if (dwCompressedSize < dwRealSize)
        {
            int cbOutBuffer = (int)dwRealSize;
            int cbInBuffer = (int)dwCompressedSize;

            if (!SCompDecompress((char *)pvTable, &cbOutBuffer, (char *)pbCompressed, cbInBuffer))
                nError = GetLastError();

            // Free the temporary buffer
            FREEMEM(pbCompressed);
        }
    }
    else
    {
        nError = GetLastError();
    }

    BSWAP_ARRAY32_UNSIGNED(pvTable, dwRealSize);
    return nError;
}

void CalculateRawSectorOffset(
    ULONGLONG & RawFilePos,
    TMPQFile * hf,
    DWORD dwSectorOffset)
{
    //
    // Some MPQ protectors place the sector offset table after the actual file data.
    // Sector offsets in the sector offset table are negative. When added
    // to MPQ file offset from the block table entry, the result is a correct
    // position of the file data in the MPQ.
    //
    // The position of sector table must be always within the MPQ, however.
    // When a negative sector offset is found, we make sure that we make the addition
    // just in 32-bits, and then add the MPQ offset.
    //

    if (dwSectorOffset & 0x80000000)
    {
        RawFilePos = hf->ha->MpqPos + ((DWORD)hf->pFileEntry->ByteOffset + dwSectorOffset);
    }
    else
    {
        RawFilePos = hf->RawFilePos + dwSectorOffset;
    }

    // We also have to add patch header size, if patch header is present
    if (hf->PatchInfo != NULL)
        RawFilePos += hf->PatchInfo->dwLength;
}

// Allocates sector buffer and sector offset table
int AllocateSectorBuffer(TMPQFile * hf)
{
    TMPQArchive * ha = hf->ha;

    // Caller of AllocateSectorBuffer must ensure these
    assert(hf->pbFileSector == NULL);
    assert(hf->pFileEntry != NULL);
    assert(hf->dwDataSize != 0);
    assert(hf->ha != NULL);

    // Determine the file sector size and allocate buffer for it
    hf->dwSectorSize = (hf->pFileEntry->dwFlags & MPQ_FILE_SINGLE_UNIT) ? hf->dwDataSize : ha->dwSectorSize;
    hf->pbFileSector = ALLOCMEM(BYTE, hf->dwSectorSize);
    hf->dwSectorOffs = SFILE_INVALID_POS;

    // Return result
    return (hf->pbFileSector != NULL) ? (int)ERROR_SUCCESS : (int)ERROR_NOT_ENOUGH_MEMORY;
}

// Allocates sector offset table
int AllocatePatchInfo(TMPQFile * hf, bool bLoadFromFile)
{
    TMPQArchive * ha = hf->ha;
    DWORD dwLength = sizeof(TPatchInfo);

    // The following conditions must be true
    assert(hf->pFileEntry->dwFlags & MPQ_FILE_PATCH_FILE);
    assert(hf->PatchInfo == NULL);

__AllocateAndLoadPatchInfo:

    // Allocate space for patch header. Start with default size,
    // and if its size if bigger, then we reload them
    hf->PatchInfo = (TPatchInfo *)ALLOCMEM(BYTE, dwLength);
    if (hf->PatchInfo == NULL)
        return ERROR_NOT_ENOUGH_MEMORY;

    // Do we have to load the patch header from the file ?
    if (bLoadFromFile)
    {
        // Load the patch header
        if (!FileStream_Read(ha->pStream, &hf->RawFilePos, hf->PatchInfo, dwLength))
        {
            // Free the sector offsets
            FREEMEM(hf->PatchInfo);
            hf->PatchInfo = NULL;
            return GetLastError();
        }

        // Perform necessary swapping
        hf->PatchInfo->dwLength = BSWAP_INT32_UNSIGNED(hf->PatchInfo->dwLength);
        hf->PatchInfo->dwFlags = BSWAP_INT32_UNSIGNED(hf->PatchInfo->dwFlags);
        hf->PatchInfo->dwDataSize = BSWAP_INT32_UNSIGNED(hf->PatchInfo->dwDataSize);

        // Verify the size of the patch header
        // If it's not default size, we have to reload them
        if (hf->PatchInfo->dwLength > dwLength)
        {
            dwLength = hf->PatchInfo->dwLength;
            FREEMEM(hf->PatchInfo);
            hf->PatchInfo = NULL;

            goto __AllocateAndLoadPatchInfo;
        }

        // Patch file data size according to the patch header
        hf->dwDataSize = hf->PatchInfo->dwDataSize;
    }
    else
    {
        memset(hf->PatchInfo, 0, dwLength);
    }

    // Save the final length to the patch header
    hf->PatchInfo->dwLength = dwLength;
    hf->PatchInfo->dwFlags  = 0x80000000;
    return ERROR_SUCCESS;
}

// Allocates sector offset table
int AllocateSectorOffsets(TMPQFile * hf, bool bLoadFromFile)
{
    TMPQArchive * ha = hf->ha;
    TFileEntry * pFileEntry = hf->pFileEntry;
    DWORD dwArraySize;

    // Caller of AllocateSectorOffsets must ensure these
    assert(hf->SectorOffsets == NULL);
    assert(hf->pFileEntry != NULL);
    assert(hf->dwDataSize != 0);
    assert(hf->ha != NULL);

    // If the file is stored as single unit, just set number of sectors to 1
    if (pFileEntry->dwFlags & MPQ_FILE_SINGLE_UNIT)
    {
        hf->dwDataSectors = 1;
        hf->dwSectorCount = 1;
        return ERROR_SUCCESS;
    }

    // Calculate the number of data sectors
    hf->dwDataSectors = (hf->dwDataSize / hf->dwSectorSize);
    if (hf->dwDataSize % hf->dwSectorSize)
        hf->dwDataSectors++;

    // Calculate the number of file sectors
    hf->dwSectorCount = (hf->dwDataSize / hf->dwSectorSize) + 1;
    if (hf->dwDataSize % hf->dwSectorSize)
        hf->dwSectorCount++;
    if (pFileEntry->dwFlags & MPQ_FILE_SECTOR_CRC)
        hf->dwSectorCount++;

    // Only allocate and load the table if the file is compressed
    if (pFileEntry->dwFlags & MPQ_FILE_COMPRESSED)
    {
        __LoadSectorOffsets:

        // Allocate the sector offset table
        hf->SectorOffsets = ALLOCMEM(DWORD, hf->dwSectorCount);
        if (hf->SectorOffsets == NULL)
            return ERROR_NOT_ENOUGH_MEMORY;

        // Calculate the size of the bytes to be read
        dwArraySize = hf->dwSectorCount * sizeof(DWORD);

        // Only read from the file if we are supposed to do so
        if (bLoadFromFile)
        {
            ULONGLONG RawFilePos = hf->RawFilePos;

            if (hf->PatchInfo != NULL)
                RawFilePos += hf->PatchInfo->dwLength;

            // Load the sector offsets from the file
            if (!FileStream_Read(ha->pStream, &RawFilePos, hf->SectorOffsets, dwArraySize))
            {
                // Free the sector offsets
                FREEMEM(hf->SectorOffsets);
                hf->SectorOffsets = NULL;
                return GetLastError();
            }

            // Swap the sector positions
            BSWAP_ARRAY32_UNSIGNED(hf->SectorOffsets, dwArraySize);

            // Decrypt loaded sector positions if necessary
            if (pFileEntry->dwFlags & MPQ_FILE_ENCRYPTED)
            {
                // If we don't know the file key, try to find it.
                if (hf->dwFileKey == 0)
                {
                    hf->dwFileKey = DetectFileKeyBySectorSize(hf->SectorOffsets, dwArraySize);
                    if (hf->dwFileKey == 0)
                    {
                        FREEMEM(hf->SectorOffsets);
                        hf->SectorOffsets = NULL;
                        return ERROR_UNKNOWN_FILE_KEY;
                    }
                }

                // Decrypt sector positions
                DecryptMpqBlock(hf->SectorOffsets, dwArraySize, hf->dwFileKey - 1);
            }

            //
            // I've seen MPQs that had MPQ_FILE_SECTOR_CRC flag absent,
            // but there was one extra entry in the sector offset table
            // (Example: expansion-locale-frFR.MPQ from WoW Cataclysm BETA)
            // We detect such behavior here by verifying the value
            // of the first entry in the sector offset table
            //

            if (hf->SectorOffsets[0] == ((hf->dwSectorCount + 1) * sizeof(DWORD)))
            {
                // Free the current sector offset table
                FREEMEM(hf->SectorOffsets);
                hf->SectorOffsets = NULL;

                // Increment number of data sectors by 1 and retry
                hf->dwSectorCount++;
                goto __LoadSectorOffsets;
            }

            //
            // Check if the sector positions are correct.
            // I saw a protector who puts negative offset into the sector offset table.
            // Because there are always at least 2 sector offsets, we can check their difference
            //

            if ((hf->SectorOffsets[1] - hf->SectorOffsets[0]) > ha->dwSectorSize)
            {
                FREEMEM(hf->SectorOffsets);
                hf->SectorOffsets = NULL;
                return ERROR_FILE_CORRUPT;
            }
        }
        else
        {
            memset(hf->SectorOffsets, 0, dwArraySize);
            hf->SectorOffsets[0] = dwArraySize;
        }
    }

    return ERROR_SUCCESS;
}

int AllocateSectorChecksums(TMPQFile * hf, bool bLoadFromFile)
{
    TMPQArchive * ha = hf->ha;
    TFileEntry * pFileEntry = hf->pFileEntry;
    ULONGLONG RawFilePos;
    DWORD dwCompressedSize;
    DWORD dwCrcOffset;                      // Offset of the CRC table, relative to file offset in the MPQ
    DWORD dwCrcSize;

    // Caller of AllocateSectorChecksums must ensure these
    assert(hf->SectorChksums == NULL);
    assert(hf->SectorOffsets != NULL);
    assert(hf->pFileEntry != NULL);
    assert(hf->ha != NULL);

    // Single unit files don't have sector checksums
    if (pFileEntry->dwFlags & MPQ_FILE_SINGLE_UNIT)
        return ERROR_SUCCESS;

    // Caller must ensure that we are only called when we have sector checksums
    assert(pFileEntry->dwFlags & MPQ_FILE_SECTOR_CRC);

    // If we only have to allocate the buffer, do it
    if (bLoadFromFile == false)
    {
        // Allocate buffer for sector checksums
        hf->SectorChksums = ALLOCMEM(DWORD, hf->dwDataSectors);
        if (hf->SectorChksums == NULL)
            return ERROR_NOT_ENOUGH_MEMORY;

        memset(hf->SectorChksums, 0, hf->dwDataSectors * sizeof(DWORD));
        return ERROR_SUCCESS;
    }

    // Check size of the checksums. If zero, there aren't any
    dwCompressedSize = hf->SectorOffsets[hf->dwDataSectors + 1] - hf->SectorOffsets[hf->dwDataSectors];
    if (dwCompressedSize == 0)
        return ERROR_SUCCESS;

    // Allocate buffer for sector CRCs
    hf->SectorChksums = ALLOCMEM(DWORD, hf->dwDataSectors);
    if (hf->SectorChksums == NULL)
        return ERROR_NOT_ENOUGH_MEMORY;

    // Calculate offset of the CRC table
    dwCrcSize = hf->dwDataSectors * sizeof(DWORD);
    dwCrcOffset = hf->SectorOffsets[hf->dwDataSectors];
    CalculateRawSectorOffset(RawFilePos, hf, dwCrcOffset);

    // Now read the table from the MPQ
    return LoadMpqTable(ha, RawFilePos, hf->SectorChksums, dwCompressedSize, dwCrcSize, 0);
}

int WritePatchInfo(TMPQFile * hf)
{
    TMPQArchive * ha = hf->ha;
    TPatchInfo * pPatchInfo = hf->PatchInfo;

    // The caller must make sure that this function is only called
    // when the following is true.
    assert(hf->pFileEntry->dwFlags & MPQ_FILE_PATCH_FILE);
    assert(pPatchInfo != NULL);

    BSWAP_ARRAY32_UNSIGNED(pPatchInfo, 3 * sizeof(DWORD));
    if (!FileStream_Write(ha->pStream, &hf->RawFilePos, pPatchInfo, sizeof(TPatchInfo)))
        return GetLastError();

    return ERROR_SUCCESS;
}

int WriteSectorOffsets(TMPQFile * hf)
{
    TMPQArchive * ha = hf->ha;
    TFileEntry * pFileEntry = hf->pFileEntry;
    ULONGLONG RawFilePos = hf->RawFilePos;
    DWORD dwSectorPosLen = hf->dwSectorCount * sizeof(DWORD);

    // The caller must make sure that this function is only called
    // when the following is true.
    assert(hf->pFileEntry->dwFlags & MPQ_FILE_COMPRESSED);
    assert(hf->SectorOffsets != NULL);

    // If file is encrypted, sector positions are also encrypted
    if (pFileEntry->dwFlags & MPQ_FILE_ENCRYPTED)
        EncryptMpqBlock(hf->SectorOffsets, dwSectorPosLen, hf->dwFileKey - 1);
    BSWAP_ARRAY32_UNSIGNED(hf->SectorOffsets, dwSectorPosLen);

    // Adjust sector offset table position, if we also have patch info
    if (hf->PatchInfo != NULL)
        RawFilePos += hf->PatchInfo->dwLength;

    // Write sector offsets to the archive
    if (!FileStream_Write(ha->pStream, &RawFilePos, hf->SectorOffsets, dwSectorPosLen))
        return GetLastError();

    // Not necessary, as the sector checksums
    // are going to be freed when this is done.
//  BSWAP_ARRAY32_UNSIGNED(hf->SectorOffsets, dwSectorPosLen);
    return ERROR_SUCCESS;
}

int WriteSectorChecksums(TMPQFile * hf)
{
    TMPQArchive * ha = hf->ha;
    ULONGLONG RawFilePos;
    TFileEntry * pFileEntry = hf->pFileEntry;
    LPBYTE pbCompressed;
    DWORD dwCompressedSize = 0;
    DWORD dwCrcSize;
    int nOutSize;
    int nError = ERROR_SUCCESS;

    // The caller must make sure that this function is only called
    // when the following is true.
    assert(hf->pFileEntry->dwFlags & MPQ_FILE_SECTOR_CRC);
    assert(hf->SectorOffsets != NULL);
    assert(hf->SectorChksums != NULL);

    // Calculate size of the checksum array
    dwCrcSize = hf->dwDataSectors * sizeof(DWORD);

    // Allocate buffer for compressed sector CRCs.
    pbCompressed = ALLOCMEM(BYTE, dwCrcSize);
    if (pbCompressed == NULL)
        return ERROR_NOT_ENOUGH_MEMORY;

    // Perform the compression
    BSWAP_ARRAY32_UNSIGNED(hf->SectorChksums, dwCrcSize);

    nOutSize = (int)dwCrcSize;
    SCompCompress((char *)pbCompressed, &nOutSize, (char *)hf->SectorChksums, (int)dwCrcSize, MPQ_COMPRESSION_ZLIB, 0, 0);
    dwCompressedSize = (DWORD)nOutSize;

    // Write the sector CRCs to the archive
    RawFilePos = hf->RawFilePos + hf->SectorOffsets[hf->dwSectorCount - 2];
    if (hf->PatchInfo != NULL)
        RawFilePos += hf->PatchInfo->dwLength;
    if (!FileStream_Write(ha->pStream, &RawFilePos, pbCompressed, dwCompressedSize))
        nError = GetLastError();

    // Not necessary, as the sector checksums
    // are going to be freed when this is done.
//  BSWAP_ARRAY32_UNSIGNED(hf->SectorChksums, dwCrcSize);

    // Store the sector CRCs
    hf->SectorOffsets[hf->dwSectorCount - 1] = hf->SectorOffsets[hf->dwSectorCount - 2] + dwCompressedSize;
    pFileEntry->dwCmpSize += dwCompressedSize;
    FREEMEM(pbCompressed);
    return nError;
}

// Frees the structure for MPQ file
void FreeMPQFile(TMPQFile *& hf)
{
    if (hf != NULL)
    {
        // If we have patch file attached to this one, free it first
        if (hf->hfPatchFile != NULL)
            FreeMPQFile(hf->hfPatchFile);

        // Then free all buffers allocated in the file structure
        if (hf->pPatchHeader != NULL)
            FREEMEM(hf->pPatchHeader);
        if (hf->pbFileData != NULL)
            FREEMEM(hf->pbFileData);
        if (hf->PatchInfo != NULL)
            FREEMEM(hf->PatchInfo);
        if (hf->SectorOffsets != NULL)
            FREEMEM(hf->SectorOffsets);
        if (hf->SectorChksums != NULL)
            FREEMEM(hf->SectorChksums);
        if (hf->pbFileSector != NULL)
            FREEMEM(hf->pbFileSector);
        FileStream_Close(hf->pStream);
        FREEMEM(hf);
        hf = NULL;
    }
}

// Frees the MPQ archive
void FreeMPQArchive(TMPQArchive *& ha)
{
    if (ha != NULL)
    {
        // First of all, free the patch archive, if any
        if (ha->haPatch != NULL)
            FreeMPQArchive(ha->haPatch);

        // Free the file names from the file table
        for (DWORD i = 0; i < ha->dwFileTableSize; i++)
        {
            if (ha->pFileTable[i].szFileName != NULL)
                FREEMEM(ha->pFileTable[i].szFileName);
            ha->pFileTable[i].szFileName = NULL;
        }

        // Then free all buffers allocated in the archive structure
        if (ha->pFileTable != NULL)
            FREEMEM(ha->pFileTable);
        if (ha->pHashTable != NULL)
            FREEMEM(ha->pHashTable);
        if (ha->pHetTable != NULL)
            FreeHetTable(ha->pHetTable);
        if (ha->pBetTable != NULL)
            FreeBetTable(ha->pBetTable);
        FileStream_Close(ha->pStream);
        FREEMEM(ha);
        ha = NULL;
    }
}

const char * GetPlainFileName(const char * szFileName)
{
    const char * szPlainName = szFileName + strlen(szFileName);

    while (szPlainName > szFileName)
    {
        if (szPlainName[0] == '\\' || szPlainName[0] == '/')
            return szPlainName + 1;
        szPlainName--;
    }

    return szPlainName;
}

bool IsInternalMpqFileName(const char * szFileName)
{
    if (szFileName[0] == '(')
    {
        if (!_stricmp(szFileName, LISTFILE_NAME) ||
           !_stricmp(szFileName, ATTRIBUTES_NAME) ||
           !_stricmp(szFileName, SIGNATURE_NAME))
        {
            return true;
        }
    }

    return false;
}

//-----------------------------------------------------------------------------
// Swapping functions

#ifndef PLATFORM_LITTLE_ENDIAN

//
// Note that those functions are implemented for Mac operating system,
// as this is the only supported platform that uses big endian.
//

// Swaps a signed 16-bit integer
int16_t SwapInt16(uint16_t data)
{
	return (int16_t)CFSwapInt16(data);
}

// Swaps an unsigned 16-bit integer
uint16_t SwapUInt16(uint16_t data)
{
	return CFSwapInt16(data);
}

// Swaps signed 32-bit integer
int32_t SwapInt32(uint32_t data)
{
	return (int32_t)CFSwapInt32(data);
}

// Swaps an unsigned 32-bit integer
uint32_t SwapUInt32(uint32_t data)
{
	return CFSwapInt32(data);
}

// Swaps signed 64-bit integer
int64_t SwapInt64(int64_t data)
{
       return (int64_t)CFSwapInt64(data);
}

// Swaps an unsigned 64-bit integer
uint64_t SwapUInt64(uint64_t data)
{
       return CFSwapInt64(data);
}

// Swaps array of unsigned 16-bit integers
void ConvertUInt16Buffer(void * ptr, size_t length)
{
    uint16_t * buffer = (uint16_t *)ptr;
    uint32_t nElements = (uint32_t)(length / sizeof(uint16_t));

    while (nElements-- > 0)
	{
		*buffer = SwapUInt16(*buffer);
		buffer++;
	}
}

// Swaps array of unsigned 32-bit integers
void ConvertUInt32Buffer(void * ptr, size_t length)
{
    uint32_t * buffer = (uint32_t *)ptr;
    uint32_t nElements = (uint32_t)(length / sizeof(uint32_t));

	while (nElements-- > 0)
	{
		*buffer = SwapUInt32(*buffer);
		buffer++;
	}
}

// Swaps array of unsigned 64-bit integers
void ConvertUInt64Buffer(void * ptr, size_t length)
{
    uint64_t * buffer = (uint64_t *)ptr;
    uint32_t nElements = (uint32_t)(length / sizeof(uint64_t));

	while (nElements-- > 0)
	{
		*buffer = SwapUInt64(*buffer);
		buffer++;
	}
}

// Swaps the TMPQUserData structure
void ConvertTMPQUserData(void *userData)
{
	TMPQUserData * theData = (TMPQUserData *)userData;

	theData->dwID = SwapUInt32(theData->dwID);
	theData->cbUserDataSize = SwapUInt32(theData->cbUserDataSize);
	theData->dwHeaderOffs = SwapUInt32(theData->dwHeaderOffs);
	theData->cbUserDataHeader = SwapUInt32(theData->cbUserDataHeader);
}

// Swaps the TMPQHeader structure
void ConvertTMPQHeader(void *header)
{
	TMPQHeader2 * theHeader = (TMPQHeader2 *)header;

	theHeader->dwID = SwapUInt32(theHeader->dwID);
	theHeader->dwHeaderSize = SwapUInt32(theHeader->dwHeaderSize);
	theHeader->dwArchiveSize = SwapUInt32(theHeader->dwArchiveSize);
	theHeader->wFormatVersion = SwapUInt16(theHeader->wFormatVersion);
	theHeader->wSectorSize = SwapUInt16(theHeader->wSectorSize);
	theHeader->dwHashTablePos = SwapUInt32(theHeader->dwHashTablePos);
	theHeader->dwBlockTablePos = SwapUInt32(theHeader->dwBlockTablePos);
	theHeader->dwHashTableSize = SwapUInt32(theHeader->dwHashTableSize);
	theHeader->dwBlockTableSize = SwapUInt32(theHeader->dwBlockTableSize);

	if (theHeader->wFormatVersion >= MPQ_FORMAT_VERSION_2)
	{
		// Swap the hi-block table position
		theHeader->HiBlockTablePos64 = SwapUInt64(theHeader->HiBlockTablePos64);

        theHeader->wHashTablePosHi = SwapUInt16(theHeader->wHashTablePosHi);
		theHeader->wBlockTablePosHi = SwapUInt16(theHeader->wBlockTablePosHi);

        if (theHeader->wFormatVersion >= MPQ_FORMAT_VERSION_3)
    	{
            theHeader->ArchiveSize64 = SwapUInt64(theHeader->ArchiveSize64);
            theHeader->BetTablePos64 = SwapUInt64(theHeader->BetTablePos64);
            theHeader->HetTablePos64 = SwapUInt64(theHeader->HetTablePos64);

            if (theHeader->wFormatVersion >= MPQ_FORMAT_VERSION_4)
        	{
                theHeader->HashTableSize64    = SwapUInt64(theHeader->HashTableSize64);
                theHeader->BlockTableSize64   = SwapUInt64(theHeader->BlockTableSize64);
                theHeader->HiBlockTableSize64 = SwapUInt64(theHeader->HiBlockTableSize64);
                theHeader->HetTableSize64     = SwapUInt64(theHeader->HetTableSize64);
                theHeader->BetTableSize64     = SwapUInt64(theHeader->BetTableSize64);
            }
        }
	}
}

#endif  // PLATFORM_LITTLE_ENDIAN