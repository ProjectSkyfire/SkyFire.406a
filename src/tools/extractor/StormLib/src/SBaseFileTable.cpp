/*****************************************************************************/
/* SBaseFileTable.cpp                     Copyright (c) Ladislav Zezula 2010 */
/*---------------------------------------------------------------------------*/
/* Description: Common handler for classic and new hash&block tables         */
/*---------------------------------------------------------------------------*/
/*   Date    Ver   Who  Comment                                              */
/* --------  ----  ---  -------                                              */
/* 06.09.10  1.00  Lad  The first version of SBaseFileTable.cpp              */
/*****************************************************************************/

#define __STORMLIB_SELF__
#define __INCLUDE_CRYPTOGRAPHY__
#include "StormLib.h"
#include "StormCommon.h"

#if defined(WIN32) || defined(WIN64)
#pragma warning( disable : 4018 4101)
#endif

//-----------------------------------------------------------------------------
// Local defines

#define HET_TABLE_SIGNATURE 0x1A544548      // 'HET\x1a'
#define BET_TABLE_SIGNATURE 0x1A544542      // 'BET\x1a'

//-----------------------------------------------------------------------------
// Local structures

// Structure for HET table header
typedef struct _HET_TABLE_HEADER
{
    DWORD dwTableSize;                      // Size of the entire hash table, including the header (in bytes)
    DWORD dwFileCount;                      // Number of used file entries in the HET table
    DWORD dwHashTableSize;                  // Size of the hash table, (in bytes)
    DWORD dwHashEntrySize;                  // Effective size of the hash entry (in bits)
    DWORD dwTotalIndexSize;                 // Total of index entry, in bits
    DWORD dwUnknown14;
    DWORD dwIndexSize;                      // Effective size of the index entry
    DWORD dwBlockTableSize;                 // Size of the block index subtable (in bytes)
} HET_TABLE_HEADER, *PHET_TABLE_HEADER;

// Structure for BET table header
typedef struct _BET_TABLE_HEADER
{
    DWORD dwTableSize;                      // Size of the entire hash table, including the header (in bytes)
    DWORD dwFileCount;                      // Number of files in the ext block table
    DWORD dwUnknown08;
    DWORD dwTableEntrySize;                 // Size of one table entry (in bits)
    DWORD dwBitIndex_FilePos;               // Bit index of the file position (within the entry record)
    DWORD dwBitIndex_FSize;                 // Bit index of the file size (within the entry record)
    DWORD dwBitIndex_CSize;                 // Bit index of the compressed size (within the entry record)
    DWORD dwBitIndex_FlagIndex;             // Bit index of the flag index (within the entry record)
    DWORD dwBitIndex_Unknown;               // Bit index of the ??? (within the entry record)
    DWORD dwFilePosBits;                    // Bit size of file position (in the entry record)
    DWORD dwFileSizeBits;                   // Bit size of file size (in the entry record)
    DWORD dwCmpSizeBits;                    // Bit size of compressed file size (in the entry record)
    DWORD dwFlagsBits;                      // Bit size of flags index (in the entry record)
    DWORD dwUnknownBits;                    // Bit size of ??? (in the entry record)
    DWORD TotalNameHash2Size;               // Total size of the NameHashPart2 (in bits)
    DWORD dwUnknown3C;
    DWORD NameHash2Size;                    // Effective size of NameHashPart2 (in bits)
    DWORD dwUnknown44;
    DWORD dwFlagCount;                      // Number of flags in the following array
} BET_TABLE_HEADER, *PBET_TABLE_HEADER;

typedef struct _MPQ_FILE_BLOCK_ENTRY
{
    DWORD dwFilePosLo;
    DWORD dwFilePosHi;
    DWORD dwCmpSizeLo;
    DWORD dwCmpSizeHi;
    DWORD dwFileSizeLo;
    DWORD dwFileSizeHi;
    DWORD dwFlags;
    DWORD result64_lo;
    DWORD result64_hi;
    DWORD result32;
    DWORD result128_1;
    DWORD result128_2;
    DWORD result128_3;
    DWORD result128_4;
    USHORT field_38;
} MPQ_FILE_BLOCK_ENTRY, *PMPQ_FILE_BLOCK_ENTRY;

// Structure for bit array
typedef struct _BIT_ARRAY
{
    void LoadBits(unsigned int nBitPosition, 
                  unsigned int nBitLength, 
                  void * pvBuffer, 
                  int nResultSize);

    DWORD NumberOfBits;                     // Total number of bits that are available
    BYTE Elements[1];                       // Array of elements (variable length)
} BIT_ARRAY, *PBIT_ARRAY;

// Header for HET and BET tables
struct TMPQExtTable
{
    DWORD dwSignature;                      // 'HET\x1A' or 'BET\x1A'
    DWORD dwVersion;                        // Version. Seems to be always 1
    DWORD dwDataSize;                       // Size of the contained table

    // Followed by the table header
    // Followed by the table data
};

// Structure for parsed HET table
struct TMPQHetTable
{
    DWORD      dwTotalIndexSize;            // Size of one index entry (in bits)
    DWORD      field_4;
    DWORD      dwIndexSize;                 // Effective size of the index entry
    LPBYTE     pHashPart1;                  // Array of HashPart1 values (see GetFileIndex_HetBet() for more info)
    PBIT_ARRAY pBlockIndexes;
    DWORD      dwTableSize;
    DWORD      dwFileCount;
    DWORD      dwHashBitSize;               // Effective number of bits in the hash
    ULONGLONG  AndMask64;
    ULONGLONG  OrMask64;
};

// Structure for parsed BET table
struct TMPQBetTable
{
    PBIT_ARRAY pHashPart2;                  // Bit array of NameHashPart2 values (see GetFileIndex_HetBet() for more info)
    PBIT_ARRAY pBlockTable;                 // Bit-based block table
    LPDWORD pFileFlags;                     // Array of file flags

    DWORD dwTableEntrySize;                 // Size of one table entry, in bits
    DWORD dwBitIndex_FilePos;               // Bit index of the file position in the table entry
    DWORD dwBitIndex_FSize;                 // Bit index of the file size in the table entry
    DWORD dwBitIndex_CSize;                 // Bit index of the compressed size in the table entry
    DWORD dwBitIndex_FlagIndex;             // Bit index of the flag index in the table entry
    DWORD dwBitIndex_Unknown;               // Bit index of ??? in the table entry
    DWORD dwFilePosBits;                    // Size of file offset (in bits) within table entry
    DWORD dwFileSizeBits;                   // Size of file size (in bits) within table entry
    DWORD dwCmpSizeBits;                    // Size of compressed file size (in bits) within table entry
    DWORD dwFlagsBits;                      // Size of flag index (in bits) within table entry
    DWORD dwUnknownBits;                    // Size of ??? (in bits) within table entry
    DWORD TotalNameHash2Size;               // Total size of NameHashPart2
    DWORD field_48;
    DWORD NameHash2Size;                    // Effective size of the NameHashPart2
    DWORD dwFileCount;                      // Number of used entries in the table
    DWORD dwFlagCount;                      // Number of entries in pFileFlags

//  vector<INT64>  field_5C;
//  vector<DWORD>  field_74;
//  vector<INT128> field_8C;
//  vector<BYTE>   field_A4;
    DWORD dwOpenFlags;
};

//-----------------------------------------------------------------------------
// Support functions for BIT_ARRAY

static PBIT_ARRAY CreateBitArray(
    DWORD NumberOfBits, 
    BYTE FillValue)
{
    PBIT_ARRAY pBitArray;
    size_t nSize = sizeof(BIT_ARRAY) + (NumberOfBits + 0x07) / 8;

    // Allocate the bit array
    pBitArray = (PBIT_ARRAY)ALLOCMEM(BYTE, nSize);
    if (pBitArray != NULL)
    {
        memset(pBitArray, FillValue, nSize);
        pBitArray->NumberOfBits = NumberOfBits;
    }

    return pBitArray;
}

void BIT_ARRAY::LoadBits(
    unsigned int nBitPosition, 
    unsigned int nBitLength, 
    void * pvBuffer, 
    int nResultByteSize)
{
    unsigned char * pbBuffer;
    unsigned int nNextBytePosition;                     // EBX
    unsigned int nBytePosition = (nBitPosition / 8);    // ESI
    unsigned int nByteLength = (nBitLength / 8);        // ECX
    unsigned int nBitOffset = (nBitPosition & 0x07);    // AL
    unsigned char BitBuffer;

    // Adjust the buffer pointer
    pbBuffer = (unsigned char *)pvBuffer - nBytePosition;
    nNextBytePosition = nBytePosition + 1;

    // Copy whole bytes, if any
    while (nByteLength > 0)
    {
        if (nBitOffset != 0)
        {
            BitBuffer = (unsigned char)((Elements[nBytePosition] >> nBitOffset) | (Elements[nNextBytePosition] << (0x08 - nBitOffset)));
        }
        else
        {
            BitBuffer = Elements[nBytePosition];
        }

        pbBuffer[nBytePosition++] = BitBuffer;
        nNextBytePosition++;
        nByteLength--;
    }

    // Get the rest of the bits
    nBitLength = (nBitLength & 0x07);
    if (nBitLength != 0)
    {
        BitBuffer = Elements[nBytePosition];
        pbBuffer[nBytePosition] = (unsigned char)(BitBuffer >> nBitOffset);

        if ((8 - nBitOffset) < nBitLength)
            pbBuffer[nBytePosition] = (unsigned char)((Elements[nNextBytePosition] << (8 - nBitOffset)) | (Elements[nBytePosition] >> nBitOffset));

        pbBuffer[nBytePosition] &= (0x01 << nBitLength) - 1;
    }
}

//-----------------------------------------------------------------------------
// Support for TMPQHetTable

static TMPQHetTable * CreateHetTable(DWORD dwTableSize, DWORD dwFileCount, DWORD dwHashBitSize)
{
    TMPQHetTable * pHetTable;
    ULONGLONG MulResult;

    pHetTable = ALLOCMEM(TMPQHetTable, 1);
    if (pHetTable != NULL)
    {
        pHetTable->dwTotalIndexSize = 0;
        pHetTable->field_4          = 0;
        pHetTable->dwIndexSize      = 0;
        pHetTable->pHashPart1       = NULL;
        pHetTable->pBlockIndexes    = NULL;
        pHetTable->dwTableSize      = dwTableSize;
        pHetTable->dwFileCount      = dwFileCount;
        pHetTable->dwHashBitSize    = dwHashBitSize;
        pHetTable->AndMask64        = 0;

        // The table size in bytes is calculated as (NumberOfFiles * 1.33333333) / 8
        MulResult = 0xAAAAAAAB4ULL * dwFileCount;
        assert(pHetTable->dwTableSize == (DWORD)(MulResult >> 32) / 8);

        // Calculate masks
        if (dwHashBitSize != 0x40)
            pHetTable->AndMask64 = (ULONGLONG)1 << dwHashBitSize;
        pHetTable->AndMask64--;

        pHetTable->OrMask64 = (ULONGLONG)1 << (dwHashBitSize - 1);
    }

    return pHetTable;
}

static TMPQHetTable * TranslateHetTable(TMPQExtTable * pExtTable)
{
    HET_TABLE_HEADER HetHeader;
    TMPQHetTable * pHetTable = NULL;
    LPBYTE pbSrcData = (LPBYTE)(pExtTable + 1);

    // Sanity check
    assert(pExtTable->dwSignature == HET_TABLE_SIGNATURE);
    assert(pExtTable->dwVersion == 1);

    // Verify size of the HET table
    if (pExtTable != NULL && pExtTable->dwDataSize >= sizeof(HET_TABLE_HEADER))
    {
        // Copy the table header in order to have it aligned and swapped
        memcpy(&HetHeader, pbSrcData, sizeof(HET_TABLE_HEADER));
        BSWAP_ARRAY32_UNSIGNED(&HetHeader, sizeof(HET_TABLE_HEADER));
        pbSrcData += sizeof(HET_TABLE_HEADER);

        // Verify the size of the table in the header
        if (HetHeader.dwTableSize == pExtTable->dwDataSize)
        {
            // Create translated table
            pHetTable = CreateHetTable(HetHeader.dwHashTableSize, HetHeader.dwFileCount, HetHeader.dwHashEntrySize);
            if (pHetTable != NULL)
            {
                // Save the total index size and effective index size
                pHetTable->dwTotalIndexSize = HetHeader.dwTotalIndexSize;
                pHetTable->field_4          = HetHeader.dwUnknown14;
                pHetTable->dwIndexSize      = HetHeader.dwIndexSize;

                // Copy the hash table
                pHetTable->pHashPart1 = ALLOCMEM(BYTE, HetHeader.dwHashTableSize);
                if (pHetTable->pHashPart1 != NULL)
                    memcpy(pHetTable->pHashPart1, pbSrcData, HetHeader.dwHashTableSize);
                pbSrcData += HetHeader.dwHashTableSize;

                // Copy the block index table
                pHetTable->pBlockIndexes = CreateBitArray(HetHeader.dwBlockTableSize * 8, 0xFF);
                if (pHetTable->pBlockIndexes != NULL)
                    memcpy(pHetTable->pBlockIndexes->Elements, pbSrcData, HetHeader.dwBlockTableSize);
                pbSrcData += HetHeader.dwBlockTableSize;
            }
        }
    }

    return pHetTable;
}

void FreeHetTable(TMPQHetTable * pHetTable)
{
    if (pHetTable != NULL)
    {
        if (pHetTable->pHashPart1 != NULL)
            FREEMEM(pHetTable->pHashPart1);
        if (pHetTable->pBlockIndexes != NULL)
            FREEMEM(pHetTable->pBlockIndexes);

        FREEMEM(pHetTable);
    }
}

//-----------------------------------------------------------------------------
// Support for BET table

TMPQBetTable * CreateBetTable(DWORD dwFileCount, DWORD dwOpenFlags)
{
    TMPQBetTable * pBetTable;

    // Allocate BET table
    pBetTable = ALLOCMEM(TMPQBetTable, 1);
    if (pBetTable != NULL)
    {
        memset(pBetTable, 0, sizeof(TMPQBetTable));
        pBetTable->dwFileCount = dwFileCount;
        pBetTable->dwOpenFlags = dwOpenFlags;
/*
        if (dwOpenFlags & 0x80)
            field_74.resize(dwFileCount);

        if (dwOpenFlags & 0x40)
            field_8C.resize(dwFileCount);

        if (dwOpenFlags & 0x100)
            field_5C.resize(dwFileCount);

        if (dwOpenFlags & 0x1000)
            field_A4.resize((dwFileCount + 7) >> 0x03);
*/
    }

    return pBetTable;
}

static TMPQBetTable * TranslateBetTable(TMPQExtTable * pExtTable, DWORD dwOpenFlags)
{
    BET_TABLE_HEADER BetHeader;
    TMPQBetTable * pBetTable = NULL;
    LPBYTE pbSrcData = (LPBYTE)(pExtTable + 1);
    DWORD LengthInBytes;

    // Sanity check
    assert(pExtTable->dwSignature == BET_TABLE_SIGNATURE);
    assert(pExtTable->dwVersion == 1);

    // Verify size of the HET table
    if (pExtTable != NULL && pExtTable->dwDataSize >= sizeof(BET_TABLE_HEADER))
    {
        // Copy the table header in order to have it aligned and swapped
        memcpy(&BetHeader, pbSrcData, sizeof(BET_TABLE_HEADER));
        BSWAP_ARRAY32_UNSIGNED(&BetHeader, sizeof(BET_TABLE_HEADER));
        pbSrcData += sizeof(BET_TABLE_HEADER);

        // Verify the size of the table in the header
        if (BetHeader.dwTableSize == pExtTable->dwDataSize)
        {
            // Create translated table
            pBetTable = CreateBetTable(BetHeader.dwFileCount, 0);
            if (pBetTable != NULL)
            {
                // Copy the variables from the header to the BetTable
                pBetTable->dwTableEntrySize     = BetHeader.dwTableEntrySize;
                pBetTable->dwBitIndex_FilePos   = BetHeader.dwBitIndex_FilePos;
                pBetTable->dwBitIndex_FSize     = BetHeader.dwBitIndex_FSize;
                pBetTable->dwBitIndex_CSize     = BetHeader.dwBitIndex_CSize;
                pBetTable->dwBitIndex_FlagIndex = BetHeader.dwBitIndex_FlagIndex;
                pBetTable->dwBitIndex_Unknown   = BetHeader.dwBitIndex_Unknown;
                pBetTable->dwFilePosBits        = BetHeader.dwFilePosBits;
                pBetTable->dwFileSizeBits       = BetHeader.dwFileSizeBits;
                pBetTable->dwCmpSizeBits        = BetHeader.dwCmpSizeBits;
                pBetTable->dwFlagsBits          = BetHeader.dwFlagsBits;
                pBetTable->dwUnknownBits        = BetHeader.dwUnknownBits;

                // Allocate array for flags
                if (BetHeader.dwFlagCount != 0)
                {
                    LPDWORD FileFlags = (LPDWORD)pbSrcData;

                    // Allocate array for file flags and load it
                    pBetTable->pFileFlags = ALLOCMEM(DWORD, BetHeader.dwFlagCount);
                    if (pBetTable->pFileFlags != NULL)
                    {
                        for (int i = 0; i < BetHeader.dwFlagCount; i++)
                            pBetTable->pFileFlags[i] = BSWAP_INT32_UNSIGNED(FileFlags[i]);
                    }

                    // Move the source pointer
                    pbSrcData += BetHeader.dwFlagCount * sizeof(DWORD);
                    pBetTable->dwFlagCount = BetHeader.dwFlagCount;
                }

                // Load the block table
                pBetTable->pBlockTable = CreateBitArray(pBetTable->dwTableEntrySize * pBetTable->dwFileCount, 0);
                LengthInBytes = (pBetTable->pBlockTable->NumberOfBits + 7) / 8;
                if (pBetTable->pBlockTable != NULL)
                    memcpy(pBetTable->pBlockTable->Elements, pbSrcData, LengthInBytes);
                pbSrcData += LengthInBytes;

                // Fill the size of one entry
                pBetTable->TotalNameHash2Size = BetHeader.TotalNameHash2Size;
                pBetTable->field_48           = BetHeader.dwUnknown3C;
                pBetTable->NameHash2Size      = BetHeader.NameHash2Size;

                //
                pBetTable->pHashPart2 = CreateBitArray(pBetTable->TotalNameHash2Size * pBetTable->dwFileCount, 0);
                LengthInBytes = (pBetTable->pHashPart2->NumberOfBits + 7) / 8;
                if (pBetTable->pHashPart2 != NULL)
                    memcpy(pBetTable->pHashPart2->Elements, pbSrcData, LengthInBytes);
                pbSrcData += LengthInBytes;
            }
        }
    }

    return pBetTable;
}

void FreeBetTable(TMPQBetTable * pBetTable)
{
    if (pBetTable != NULL)
    {
        if (pBetTable->pBlockTable != NULL)
            FREEMEM(pBetTable->pBlockTable);
        if (pBetTable->pFileFlags != NULL)
            FREEMEM(pBetTable->pFileFlags);
        if (pBetTable->pHashPart2 != NULL)
            FREEMEM(pBetTable->pHashPart2);

        FREEMEM(pBetTable);
    }
}

//-----------------------------------------------------------------------------
// Local functions

// Returns a hash table entry in the following order:
// 1) A hash table entry with the neutral locale
// 2) A hash table entry with any other locale
// 3) NULL
static TMPQHash * GetHashEntryAny(TMPQArchive * ha, const char * szFileName)
{
    TMPQHash * pHashNeutral = NULL;
    TMPQHash * pFirstHash = GetFirstHashEntry(ha, szFileName);
    TMPQHash * pHashAny = NULL;
    TMPQHash * pHash = pFirstHash;

    // Parse the found hashes
    while (pHash != NULL)
    {
        // If we found neutral hash, remember it
        if (pHash->lcLocale == 0)
            pHashNeutral = pHash;
        if (pHashAny == NULL)
            pHashAny = pHash;

        // Get the next hash entry for that file
        pHash = GetNextHashEntry(ha, pFirstHash, pHash);
    }

    // At the end, return neutral hash (if found), otherwise NULL
    return (pHashNeutral != NULL) ? pHashNeutral : pHashAny;
}

// Returns a hash table entry in the following order:
// 1) A hash table entry with the preferred locale
// 2) A hash table entry with the neutral locale
// 3) NULL
static TMPQHash * GetHashEntryLocale(TMPQArchive * ha, const char * szFileName, LCID lcLocale)
{
    TMPQHash * pHashNeutral = NULL;
    TMPQHash * pFirstHash = GetFirstHashEntry(ha, szFileName);
    TMPQHash * pHash = pFirstHash;

    // Parse the found hashes
    while (pHash != NULL)
    {
        // If the locales match, return it
        if (pHash->lcLocale == lcLocale)
            return pHash;

        // If we found neutral hash, remember it
        if (pHash->lcLocale == 0)
            pHashNeutral = pHash;

        // Get the next hash entry for that file
        pHash = GetNextHashEntry(ha, pFirstHash, pHash);
    }

    // At the end, return neutral hash (if found), otherwise NULL
    return pHashNeutral;
}

// Returns a hash table entry in the following order:
// 1) A hash table entry with the preferred locale
// 2) NULL
static TMPQHash * GetHashEntryExact(TMPQArchive * ha, const char * szFileName, LCID lcLocale)
{
    TMPQHash * pFirstHash = GetFirstHashEntry(ha, szFileName);
    TMPQHash * pHash = pFirstHash;

    // Parse the found hashes
    while (pHash != NULL)
    {
        // If the locales match, return it
        if (pHash->lcLocale == lcLocale)
            return pHash;

        // Get the next hash entry for that file
        pHash = GetNextHashEntry(ha, pFirstHash, pHash);
    }

    // Not found
    return NULL;
}

static TMPQExtTable * LoadExtTable(
    TMPQArchive * ha, 
    ULONGLONG ByteOffset, 
    ULONGLONG Size, 
    DWORD dwKey)
{
    ULONGLONG FileOffset;
    TMPQExtTable * pCompressed = NULL;      // Compressed table
    TMPQExtTable * pExtTable;               // Uncompressed table

    // Allocate size for the compressed table
    pExtTable = (TMPQExtTable *)ALLOCMEM(BYTE, Size);
    if (pExtTable != NULL)
    {
        // Load the block from the MPQ
        FileOffset = ByteOffset;
        if (!FileStream_Read(ha->pStream, &FileOffset, pExtTable, Size))
        {
            FREEMEM(pExtTable);
            return NULL;
        }

        // Swap the ext table header
        BSWAP_ARRAY32_UNSIGNED(pExtTable, sizeof(TMPQExtTable));

        // Decrypt the block
        BSWAP_ARRAY32_UNSIGNED(pExtTable + 1, pExtTable->dwDataSize);
        DecryptMpqBlock(pExtTable + 1, pExtTable->dwDataSize, dwKey);
        BSWAP_ARRAY32_UNSIGNED(pExtTable + 1, pExtTable->dwDataSize);

        // If the table is compressed, decompress it
        if ((pExtTable->dwDataSize + sizeof(TMPQExtTable)) > Size)
        {
            pCompressed = pExtTable;
            pExtTable = (TMPQExtTable *)ALLOCMEM(BYTE, sizeof(TMPQExtTable) + pCompressed->dwDataSize);
            if (pExtTable != NULL)
            {
                int cbOutBuffer = (int)pCompressed->dwDataSize;
                int cbInBuffer = (int)Size;

                // Decompress the XXX block
                pExtTable->dwSignature = pCompressed->dwSignature;
                pExtTable->dwVersion   = pCompressed->dwVersion;
                pExtTable->dwDataSize  = pCompressed->dwDataSize;
                SCompDecompress((char *)(pExtTable + 1), &cbOutBuffer, (char *)(pCompressed + 1), cbInBuffer);
            }

            // Free the compressed block
            FREEMEM(pCompressed);
        }
    }

    // Return the decompressed table to the caller
    return pExtTable;
}

//-----------------------------------------------------------------------------
// Support for file tables - hash table, block table, hi-block table, 
// (attributes) and (listfile)

// This function recalculates raw position of hash table, 
// block table and hi-block table.
static void CalculateTablePositions(TMPQArchive * ha, bool bNeedHiBlockTable)
{
    TMPQHeader * pHeader = ha->pHeader;
    ULONGLONG TablePos;                     // A table position, relative to the begin of the MPQ

    // Find the first block that is beyond the last file
    FindFreeMpqSpace(ha, &TablePos);

    // We don't support saving archives with HET and/or BET tables
    assert(ha->pHetTable == NULL);
    assert(ha->pBetTable == NULL);

    // Next following is the hash table
    pHeader->wHashTablePosHi = (USHORT)(TablePos >> 32);
    pHeader->dwHashTablePos = (DWORD)(TablePos);
    pHeader->HashTableSize64 = pHeader->dwHashTableSize * sizeof(TMPQHash);
    TablePos += pHeader->HashTableSize64;

    // ... followed by the block table
    pHeader->wBlockTablePosHi = (USHORT)(TablePos >> 32);
    pHeader->dwBlockTablePos = (DWORD)TablePos;
    pHeader->BlockTableSize64 = pHeader->dwBlockTableSize * sizeof(TMPQBlock);
    TablePos += pHeader->BlockTableSize64;

    // Hi-block table follows the old block table
    // Note that we will only use hi-block table
    // if the current position is beyond 4 GB.
    if (bNeedHiBlockTable)
    {
        pHeader->HiBlockTablePos64 = TablePos;
        pHeader->HiBlockTableSize64 = pHeader->dwBlockTableSize * sizeof(USHORT);
        TablePos += pHeader->HiBlockTableSize64;
    }
    else
    {
        pHeader->HiBlockTablePos64 = 0;
        pHeader->HiBlockTableSize64 = 0;
    }

    // Update archive size in the header
    pHeader->dwArchiveSize = (DWORD)TablePos;
    pHeader->ArchiveSize64 = TablePos;
}

int LoadHashTable(TMPQArchive * ha)
{
    TMPQHeader * pHeader = ha->pHeader;
    ULONGLONG ByteOffset;
    TMPQHash * pHashTable;
    LPBYTE pbCompressed;
    DWORD dwTableSize = pHeader->dwHashTableSize * sizeof(TMPQHash);
    DWORD dwCmpSize = (DWORD)pHeader->HashTableSize64;
    int nError;

    // Allocate buffer for the hash table
    // Note: pHeader->dwHashTableSize can be zero !!
    pHashTable = ALLOCMEM(TMPQHash, pHeader->dwHashTableSize + 1);
    if (pHashTable == NULL)
        return ERROR_NOT_ENOUGH_MEMORY;

    // Load the table from the MPQ, with decompression
    ByteOffset = ha->MpqPos + MAKE_OFFSET64(pHeader->wHashTablePosHi, pHeader->dwHashTablePos);
    nError = LoadMpqTable(ha, ByteOffset, pHashTable, dwCmpSize, dwTableSize, MPQ_KEY_HASH_TABLE);
    if (nError != ERROR_SUCCESS)
    {
        FREEMEM(pHashTable);
        pHashTable = NULL;
        return nError;
    }

    // Store the hash table to the MPQ
    ha->pHashTable = pHashTable;
    return ERROR_SUCCESS;
}

int BuildFileTable(TMPQArchive * ha, ULONGLONG FileSize)
{
    TFileEntry * pFileTable;
    TFileEntry * pFileEntry;
    TMPQHeader * pHeader = ha->pHeader;
    TMPQBlock * pBlockTable = NULL;
    TMPQBlock * pBlock = NULL;
    ULONGLONG ByteOffset;
    int nError = ERROR_SUCCESS;

    // Sanity checks
    assert(ha->dwFileTableSize == 0);
    assert(ha->dwFileTableMax == 0);
    assert(ha->pHashTable != NULL);

    // Setup the size of the file table
    ha->dwFileTableSize = pHeader->dwBlockTableSize;
    ha->dwFileTableMax = ha->dwFileTableSize + 1;

    // Allocate space for the file table
    pFileTable = ALLOCMEM(TFileEntry, ha->dwFileTableMax);
    if (pFileTable == NULL)
        return ERROR_NOT_ENOUGH_MEMORY;

    // Fill the table with zeros
    memset(pFileTable, 0, ha->dwFileTableMax * sizeof(TFileEntry));

    // Allocate space for the block table
    // Note: pHeader->dwBlockTableSize can be zero !!!
    pBlockTable = ALLOCMEM(TMPQBlock, pHeader->dwBlockTableSize + 1);
    if (pBlockTable != NULL)
    {
        ULONGLONG ByteOffset = ha->MpqPos + MAKE_OFFSET64(pHeader->wBlockTablePosHi, pHeader->dwBlockTablePos);
        TMPQHash * pHashEnd = ha->pHashTable + pHeader->dwHashTableSize;
        TMPQHash * pHash;
        DWORD dwTableSize = pHeader->dwBlockTableSize * sizeof(TMPQBlock);
        DWORD dwCmpSize = (DWORD)pHeader->BlockTableSize64;

        // Fill the block table with zeros
        memset(pBlockTable, 0, dwTableSize);

        // I have found a MPQ which claimed 0x200 entries in the block table, 
        // but the file was cut and there was only 0x1A0 entries.
        // We will handle this case properly.
        if (dwTableSize == dwCmpSize && (ByteOffset + dwTableSize) > FileSize)
            dwTableSize = dwCmpSize = (DWORD)(FileSize - ByteOffset);

        //
        // One of the first cracked versions of Diablo had block table unencrypted
        // StormLib does NOT support such MPQs anymore, as they are incompatible
        // with compressed block table feature
        //

        // Load the block table
        nError = LoadMpqTable(ha, ByteOffset, pBlockTable, dwCmpSize, dwTableSize, MPQ_KEY_BLOCK_TABLE);
        if (nError == ERROR_SUCCESS)
        {
            // Merge the block table to the file table
            for (pHash = ha->pHashTable; pHash < pHashEnd; pHash++)
            {
                if (pHash->dwBlockIndex < pHeader->dwBlockTableSize)
                {
                    pBlock = pBlockTable + pHash->dwBlockIndex;
                    if (pBlock->dwFlags & MPQ_FILE_EXISTS)
                    {
                        // Get the entry
                        pFileEntry = pFileTable + pHash->dwBlockIndex;

                        // Fill the entry
                        pFileEntry->ByteOffset  = pBlock->dwFilePos;
                        pFileEntry->dwHashIndex = (DWORD)(pHash - ha->pHashTable);
                        pFileEntry->dwFileSize  = pBlock->dwFSize;
                        pFileEntry->dwCmpSize   = pBlock->dwCSize;
                        pFileEntry->dwFlags     = pBlock->dwFlags;
                        pFileEntry->lcLocale    = pHash->lcLocale;
                        pFileEntry->wPlatform   = pHash->wPlatform;
                    }
                }
            }
        }

        // Free the block table
        FREEMEM(pBlockTable);
    }
    else
    {
        nError = ERROR_NOT_ENOUGH_MEMORY;
    }

    // Load the hi-block table
    if (nError == ERROR_SUCCESS && pHeader->HiBlockTablePos64 != 0)
    {
        ULONGLONG ByteOffset;
        USHORT * pHiBlockTable = NULL;
        DWORD dwTableSize = pHeader->dwBlockTableSize * sizeof(USHORT);

        // Allocate space for the hi-block table
        // Note: pHeader->dwBlockTableSize can be zero !!!
        pHiBlockTable = ALLOCMEM(USHORT, pHeader->dwBlockTableSize + 1);
        if (pHiBlockTable != NULL)
        {
            // Load the hi-block table. It is not encrypted, nor compressed
            ByteOffset = ha->MpqPos + pHeader->HiBlockTablePos64;
            if (!FileStream_Read(ha->pStream, &ByteOffset, pHiBlockTable, dwTableSize))
                nError = GetLastError();

            // Now merge the hi-block table to the file table
            if (nError == ERROR_SUCCESS)
            {
                pFileEntry = pFileTable;

                // Add the high file offset to the base file offset.
                // We also need to swap it during the process.
                for (DWORD i = 0; i < pHeader->dwBlockTableSize; i++)
                {
                    pFileEntry->ByteOffset |= ((ULONGLONG)BSWAP_INT16_UNSIGNED(pHiBlockTable[i]) << 32);
                    pFileEntry++;
                }
            }

            // Free the hi-block table
            FREEMEM(pHiBlockTable);
        }
    }

    // If something failed, we free the file table entry
    if (nError != ERROR_SUCCESS)
    {
        FREEMEM(pFileTable);
        pFileTable = NULL;
    }

    // Assign it to the archive structure
    ha->pFileTable = pFileTable;
    return nError;
}

// Saves MPQ header, hash table, block table and hi-block table.
int SaveMPQTables(TMPQArchive * ha)
{
    TMPQHeader * pHeader = ha->pHeader;
    ULONGLONG ByteOffset;
    TMPQBlock * pBlockTable = NULL;
    TMPQHash * pHashTable = NULL;
    USHORT * pHiBlockTable = NULL;
    DWORD dwBytesToWrite;
    DWORD i;
    bool bNeedHiBlockTable = false;
    int nError = ERROR_SUCCESS;

    // Allocate temporary buffers for encrypting tables
    pHiBlockTable = ALLOCMEM(USHORT, ha->dwFileTableSize);
    pBlockTable = ALLOCMEM(TMPQBlock, ha->dwFileTableSize);
    pHashTable = ALLOCMEM(TMPQHash, ha->pHeader->dwHashTableSize);
    if (pHiBlockTable == NULL || pBlockTable == NULL || pHashTable == NULL)
        nError = ERROR_SUCCESS;

    // Construct the block table and hi-block table
    if (nError == ERROR_SUCCESS)
    {
        for (i = 0; i < ha->dwFileTableSize; i++)
        {
            // Set high 16 bits of the file offset
            pHiBlockTable[i] = (USHORT)(ha->pFileTable[i].ByteOffset >> 32);
            if (pHiBlockTable[i])
                bNeedHiBlockTable = true;

            // Set the block table
            pBlockTable[i].dwFilePos = (DWORD)ha->pFileTable[i].ByteOffset;
            pBlockTable[i].dwFSize   = ha->pFileTable[i].dwFileSize;
            pBlockTable[i].dwCSize   = ha->pFileTable[i].dwCmpSize;
            pBlockTable[i].dwFlags   = ha->pFileTable[i].dwFlags;
        }
    }

    // Calculate positions of the MPQ tables.
    // This sets HashTablePos, BlockTablePos and HiBlockTablePos, 
    // as well as the values in the MPQ header
    CalculateTablePositions(ha, bNeedHiBlockTable);

    // Write the MPQ Header
    if (nError == ERROR_SUCCESS)
    {
        // Remember the header size before swapping
        DWORD dwBytesToWrite = pHeader->dwHeaderSize;

        // Write the MPQ header
        BSWAP_TMPQHEADER(pHeader);
        if (FileStream_Write(ha->pStream, &ha->MpqPos, pHeader, dwBytesToWrite))
            ha->dwFlags &= ~MPQ_FLAG_NO_HEADER;
        else
            nError = GetLastError();
        BSWAP_TMPQHEADER(pHeader);
    }

    // Write the hash table
    if (nError == ERROR_SUCCESS)
    {
        // Copy the hash table to temporary buffer
        dwBytesToWrite = pHeader->dwHashTableSize * sizeof(TMPQHash);
        memcpy(pHashTable, ha->pHashTable, dwBytesToWrite);

        // Convert to little endian for file save
        EncryptMpqBlock(pHashTable, dwBytesToWrite, MPQ_KEY_HASH_TABLE);

        // Set the file pointer to the offset of the hash table and write it
        ByteOffset = ha->MpqPos + MAKE_OFFSET64(pHeader->wHashTablePosHi, pHeader->dwHashTablePos);
        BSWAP_ARRAY32_UNSIGNED(pHashTable, dwBytesToWrite);
        if (!FileStream_Write(ha->pStream, &ByteOffset, pHashTable, dwBytesToWrite))
            nError = GetLastError();
    }

    // Write the block table
    if (nError == ERROR_SUCCESS)
    {
        // Copy the block table to temporary buffer
        dwBytesToWrite = pHeader->dwBlockTableSize * sizeof(TMPQBlock);

        // Encrypt the block table and write it to the file
        EncryptMpqBlock(pBlockTable, dwBytesToWrite, MPQ_KEY_BLOCK_TABLE);

        // Convert to little endian for file save
        ByteOffset = ha->MpqPos + MAKE_OFFSET64(pHeader->wBlockTablePosHi, pHeader->dwBlockTablePos);
        BSWAP_ARRAY32_UNSIGNED(pBlockTable, dwBytesToWrite);
        if (!FileStream_Write(ha->pStream, &ByteOffset, pBlockTable, dwBytesToWrite))
            nError = GetLastError();
    }

    // Write the hi-block table
    if (nError == ERROR_SUCCESS && bNeedHiBlockTable)
    {
        // We expect format V2 or newer in this case
        assert(pHeader->wFormatVersion >= MPQ_FORMAT_VERSION_2);
        assert(pHeader->HiBlockTablePos64 != 0);

        // Copy the block table to temporary buffer
        dwBytesToWrite = pHeader->dwBlockTableSize * sizeof(USHORT);

        // Convert to little endian for file save
        ByteOffset = ha->MpqPos + pHeader->HiBlockTablePos64;
        BSWAP_ARRAY16_UNSIGNED(pHiBlockTable, dwBytesToWrite);
        if (!FileStream_Write(ha->pStream, &ByteOffset, pHiBlockTable, dwBytesToWrite))
            nError = GetLastError();
    }
    // Set end of file here
    if (nError == ERROR_SUCCESS)
    {
        ULONGLONG NewFileSize;

        FileStream_GetPos(ha->pStream, NewFileSize);
        FileStream_SetSize(ha->pStream, NewFileSize);
        ha->dwFlags &= ~MPQ_FLAG_CHANGED;
    }

    // Cleanup and exit
    if (pHashTable != NULL)
        FREEMEM(pHashTable);
    if (pBlockTable != NULL)
        FREEMEM(pBlockTable);
    if (pHiBlockTable != NULL)
        FREEMEM(pHiBlockTable);
    return nError;
}

//-----------------------------------------------------------------------------
// Support for HET and BET tables

int LoadHetAndBetTable(TMPQArchive * ha)
{
    TMPQExtTable * pExtTable;
    TMPQHeader * pHeader = ha->pHeader;
    int nError = ERROR_SUCCESS;

    // If the HET table position is not NULL, we expect
    // both HET and BET tables to be present.
    if (pHeader->HetTablePos64 != 0)
    {
        // Attempt to load the HET table (Hash Extended Table)
        pExtTable = LoadExtTable(ha, pHeader->HetTablePos64, pHeader->HetTableSize64, MPQ_KEY_HASH_TABLE);
        if (pExtTable != NULL)
        {
            ha->pHetTable = TranslateHetTable(pExtTable);
            if (ha->pHetTable == NULL)
                nError = ERROR_FILE_CORRUPT;
            FREEMEM(pExtTable);
        }
        else
            nError = ERROR_FILE_CORRUPT;

        // Attempt to load the HET table
        if (nError == ERROR_SUCCESS)
        {
            pExtTable = LoadExtTable(ha, pHeader->BetTablePos64, pHeader->BetTableSize64, MPQ_KEY_BLOCK_TABLE);
            if (pExtTable != NULL)
            {
                ha->pBetTable = TranslateBetTable(pExtTable, 0);
                if (ha->pBetTable == NULL)
                    nError = ERROR_FILE_CORRUPT;
                FREEMEM(pExtTable);
            }
            else
                nError = ERROR_FILE_CORRUPT;
        }
    }
    return nError;
}

//-----------------------------------------------------------------------------
// Support for finding files in the file table

// File search using HET and BET table
static TFileEntry * GetFileEntry_HetBet(
    TMPQArchive * ha, 
    const char * szFileName)
{
    TMPQHetTable * pHetTable = ha->pHetTable;
    TMPQBetTable * pBetTable = ha->pBetTable;
    ULONGLONG FileNameHash;
    ULONGLONG MaskedHash64;
    ULONGLONG AndMask64 = pHetTable->AndMask64;
    ULONGLONG OrMask64 = pHetTable->OrMask64;
    ULONGLONG NameHashPart2;
    DWORD StartIndex;
    DWORD Index;
    BYTE NameHashPart1;                 // Upper 8 bits of the masked file name hash

    // Calculate 64-bit hash of the file name
    FileNameHash = HashStringJenkins(szFileName);

    // Change the file name hash, so it only contains required
    // number of bits, and always has the highest bit set
    MaskedHash64 = (FileNameHash & AndMask64) | OrMask64;

    // Calculate the starting index to the hash table
    StartIndex = Index = (DWORD)(MaskedHash64 % pHetTable->dwTableSize);

    // Split the file name hash into two parts:
    // Part 1: The highest 8 bits of the name hash
    // Part 2: The rest of the name hash (without the highest 8 bits)
    NameHashPart1 = (BYTE)(MaskedHash64 >> (pHetTable->dwHashBitSize - 8));
    NameHashPart2 = MaskedHash64 & (AndMask64 >> 0x08);

    // Go through hash table until we find a terminator
    while (pHetTable->pHashPart1[Index] != 0)
    {
        // Did we find match ?
        if (pHetTable->pHashPart1[Index] == NameHashPart1)
        {
            ULONGLONG NameHashPart2Found = 0;
            DWORD dwBlockIndex = 0;

            // Get the index of the NameHashPart2
            pHetTable->pBlockIndexes->LoadBits(pHetTable->dwTotalIndexSize * Index, 
                                               pHetTable->dwIndexSize, 
                                              &dwBlockIndex, 
                                               4);

            // Verify the NameHashPart2 against the block table
            pBetTable->pHashPart2->LoadBits(pBetTable->TotalNameHash2Size * dwBlockIndex, 
                                            pBetTable->NameHash2Size, 
                                           &NameHashPart2Found, 
                                            8);
            if (NameHashPart2Found == NameHashPart2)
                return ha->pFileTable + dwBlockIndex;
        }

        // Move to the next entry in the primary search table
        Index = (Index + 1) % pHetTable->dwTableSize;

        // If we came to the start index again, we are done
        if (Index == StartIndex)
            break;
    }

    // File not found
    return NULL;
}

TFileEntry * GetFileEntryAny(TMPQArchive * ha, const char * szFileName)
{
    TMPQHash * pHash;
    ULONGLONG FileNameHash;
    DWORD dwFileIndex;

    // Perform search in the HET/BET tables
    if (ha->pHetTable != NULL)
        return GetFileEntry_HetBet(ha, szFileName);

    // For MPQs with classic hash table
    pHash = GetHashEntryAny(ha, szFileName);
    if (pHash != NULL && pHash->dwBlockIndex < ha->dwFileTableSize)
        return ha->pFileTable + pHash->dwBlockIndex;
    return NULL;
}

TFileEntry * GetFileEntryLocale(TMPQArchive * ha, const char * szFileName, LCID lcLocale)
{
    TMPQHash * pHash;

    // Perform search in the HET/BET tables
    if (ha->pHetTable != NULL)
        return GetFileEntry_HetBet(ha, szFileName);

    // For MPQs with classic hash table
    pHash = GetHashEntryLocale(ha, szFileName, lcLocale);
    if (pHash != NULL && pHash->dwBlockIndex < ha->dwFileTableSize)
        return ha->pFileTable + pHash->dwBlockIndex;
    return NULL;
}

TFileEntry * GetFileEntryExact(TMPQArchive * ha, const char * szFileName, LCID lcLocale)
{
    TMPQHash * pHash;
    ULONGLONG FileNameHash;
    DWORD dwFileIndex;

    // Perform search in the HET/BET tables
    if (ha->pHetTable != NULL)
        return GetFileEntry_HetBet(ha, szFileName);

    // For MPQs with classic hash table
    pHash = GetHashEntryExact(ha, szFileName, lcLocale);
    if (pHash != NULL && pHash->dwBlockIndex < ha->dwFileTableSize)
        return ha->pFileTable + pHash->dwBlockIndex;
    return NULL;
}

TFileEntry * GetFileEntryByIndex(TMPQArchive * ha, DWORD dwIndex)
{
    // For MPQs with classic hash table
    if (dwIndex < ha->dwFileTableSize)
        return ha->pFileTable + dwIndex;
    return NULL;
}

//-----------------------------------------------------------------------------
// Support for modifying MPQ tables

// Finds a free file entry. Does NOT increment table size, 
// althought it might reallocate it.
TFileEntry * FindFreeFileEntry(TMPQArchive * ha)
{
    TFileEntry * pFileTableEnd = ha->pFileTable + ha->dwFileTableSize;
    TFileEntry * pNewFileTable;
    TFileEntry * pFileEntry;
    TFileEntry * pFreeEntry;
    TMPQHash * pHash;

    // Otherwise, find a free entry within existing entries in the file table
    for (pFileEntry = ha->pFileTable; pFileEntry < pFileTableEnd; pFileEntry++)
    {
        // If that entry is free, we don't need
        // to reallocate file table
        if ((pFileEntry->dwFlags & MPQ_FILE_EXISTS) == 0)
            return pFileEntry;
    }

    // If no file entry within the existing file table is free, 
    // we try the reserve space after current file table
    if (ha->dwFileTableSize < ha->dwFileTableMax)
        return ha->pFileTable + ha->dwFileTableSize;

    // If there is still no entries left, we extend the file table
    assert(ha->dwFileTableSize == ha->dwFileTableMax);
    pNewFileTable = ALLOCMEM(TFileEntry, ha->dwFileTableMax + 0x10);
    if (pNewFileTable == NULL)
        return NULL;

    // Copy the old table to the new one
    memcpy(pNewFileTable, ha->pFileTable, ha->dwFileTableMax * sizeof(TFileEntry));
    FREEMEM(ha->pFileTable);
    ha->pFileTable = pNewFileTable;

    // Increment the maximum size of the file table
    ha->dwFileTableMax += 0x10;

    // Free entry is the one that is at the end of the current file table
    return ha->pFileTable + ha->dwFileTableSize;
}

TFileEntry * AllocateFileEntry(TMPQArchive * ha, const char * szFileName, LCID lcLocale)
{
    TFileEntry * pFileTableEnd = ha->pFileTable + ha->dwFileTableSize;
    TFileEntry * pNewFileTable;
    TFileEntry * pFileEntry;
    TMPQHash * pHash;

    // First, allocate new entry in the hash table
    pHash = AllocateHashEntry(ha, szFileName, lcLocale);
    if (pHash == NULL)
        return NULL;

    // Does the hash entry already point to an existing file entry ?
    if (pHash->dwBlockIndex < ha->pHeader->dwBlockTableSize)
    {
        // Reuse the existing file entry
        return ha->pFileTable + pHash->dwBlockIndex;
    }

    // Otherwise, find a free file entry.
    pFileEntry = FindFreeFileEntry(ha);
    if (pFileEntry == NULL)
    {
        // In case of failure, free the hash table entry
        pHash->dwName1      = 0xFFFFFFFF;
        pHash->dwName2      = 0xFFFFFFFF;
        pHash->dwBlockIndex = HASH_ENTRY_DELETED;
        return NULL;
    }

    // If the free file entry is at the end of the file table, 
    // we have to increment file table size
    if (pFileEntry == ha->pFileTable + ha->dwFileTableSize)
    {
        assert(ha->dwFileTableSize < ha->dwFileTableMax);
        ha->pHeader->dwBlockTableSize++;
        ha->dwFileTableSize++;
    }

    // Fill the hash index
    memset(pFileEntry, 0, sizeof(TFileEntry));
    pFileEntry->dwHashIndex = (DWORD)(pHash - ha->pHashTable);

    // Fill the file index to the hash table entry
    pHash->dwBlockIndex = (DWORD)(pFileEntry - ha->pFileTable);

    // Return the file entry
    return pFileEntry;
}

TFileEntry * RenameFile(
    TMPQArchive * ha, 
    const char * szFileName, 
    const char * szNewFileName)
{
    TFileEntry * pFileEntry;
    TMPQHash * pOldHash;
    TMPQHash * pNewHash;
    TMPQHash TempHash;
    char * szTempName;

    // Get the file entry for the existing file
    pOldHash = GetHashEntryExact(ha, szFileName, lcFileLocale);
    if (pOldHash == NULL)
    {
        SetLastError(ERROR_FILE_NOT_FOUND);
        return NULL;
    }

    // Free the hash table entry
    memcpy(&TempHash, pOldHash, sizeof(TMPQHash));
    memset(pOldHash, 0xFF, sizeof(TMPQHash));
    pOldHash->dwBlockIndex = HASH_ENTRY_DELETED;

    // Try to find new hash table entry
    pNewHash = AllocateHashEntry(ha, szNewFileName, lcFileLocale);
    if (pNewHash == NULL)
    {
        memcpy(pOldHash, &TempHash, sizeof(TMPQHash));
        SetLastError(ERROR_ALREADY_EXISTS);
        return NULL;
    }

    // Make new Hash table entry point to the original block table entry
    pNewHash->lcLocale     = TempHash.lcLocale;
    pNewHash->wPlatform    = TempHash.wPlatform;
    pNewHash->dwBlockIndex = TempHash.dwBlockIndex;
    pFileEntry = ha->pFileTable + TempHash.dwBlockIndex;

    // Allocate new file name
    szTempName = ALLOCMEM(char, strlen(szNewFileName) + 1);
    if (szTempName != NULL)
    {
        strcpy(szTempName, szNewFileName);
        FREEMEM(pFileEntry->szFileName);
        pFileEntry->szFileName = szTempName;
    }

    // Return the found file entry
    return pFileEntry;
}

void FreeFileEntry(
    TMPQArchive * ha, 
    TFileEntry * pFileEntry)
{
    // Clear the hash table entry
    memset(ha->pHashTable + pFileEntry->dwHashIndex, 0xFF, sizeof(TMPQHash));
    ha->pHashTable[pFileEntry->dwHashIndex].dwBlockIndex = HASH_ENTRY_DELETED;

    // Clear the block entry
    memset(pFileEntry, 0, sizeof(TFileEntry));

    // Decrement block entry size, if necessary
    if (pFileEntry == ha->pFileTable + (ha->dwFileTableSize - 1))
        ha->dwFileTableSize--;

    // Make sure that the block table has the proper size
    ha->pHeader->dwBlockTableSize = ha->dwFileTableSize;
}

//-----------------------------------------------------------------------------
// Support for finding files in the BET table

static bool GetFileBlockEntry_BetData(
    TMPQBetTable * pBetTable, 
    DWORD dwBlockIndex, 
    PMPQ_FILE_BLOCK_ENTRY pBlockEntry)
{
    if (pBetTable->pBlockTable == 0)
        return false;

    memset(pBlockEntry, 0, sizeof(MPQ_FILE_BLOCK_ENTRY));

    pBetTable->pBlockTable->LoadBits(pBetTable->dwTableEntrySize * dwBlockIndex + pBetTable->dwBitIndex_FilePos, 
                                     pBetTable->dwFilePosBits, 
                                    &pBlockEntry->dwFilePosLo, 
                                     8);

    pBetTable->pBlockTable->LoadBits(pBetTable->dwTableEntrySize * dwBlockIndex + pBetTable->dwBitIndex_FSize, 
                                     pBetTable->dwFileSizeBits, 
                                    &pBlockEntry->dwFileSizeLo, 
                                     8);

    pBetTable->pBlockTable->LoadBits(pBetTable->dwTableEntrySize * dwBlockIndex + pBetTable->dwBitIndex_CSize, 
                                     pBetTable->dwCmpSizeBits, 
                                    &pBlockEntry->dwCmpSizeLo, 
                                     8);

    if (pBetTable->dwFlagCount == 0)
        return false;

    if (pBetTable->dwFlagCount != 1)
    {
        DWORD dwFlagIndex = 0;

        // Get the flag index from the array
        pBetTable->pBlockTable->LoadBits(pBetTable->dwTableEntrySize * dwBlockIndex + pBetTable->dwBitIndex_FlagIndex, 
                                         pBetTable->dwFlagsBits, 
                                        &dwFlagIndex, 
                                         4);

        if (dwFlagIndex > pBetTable->dwFlagCount)
            return false;
        pBlockEntry->dwFlags = pBetTable->pFileFlags[dwFlagIndex];
    }
    else
    {
        pBlockEntry->dwFlags = pBetTable->pFileFlags[0];
    }

    if (pBetTable->dwOpenFlags & 0x200)
    {
        BYTE OneByte = 0;

        pBetTable->pBlockTable->LoadBits(pBetTable->dwTableEntrySize * dwBlockIndex + pBetTable->dwBitIndex_Unknown, 
                                                 pBetTable->dwUnknownBits, 
                                                &OneByte, 
                                                 1);
        pBlockEntry->field_38 = OneByte ? 1 : 0;
    }

    return true;
}

static void GetFileBlockEntry(TMPQArchive * ha, TMPQBetTable * pBetTable, PMPQ_FILE_BLOCK_ENTRY pBlockEntry, DWORD dwBlockIndex)
{
    MPQ_FILE_BLOCK_ENTRY BlockEntry;
//  LPBYTE pointer_to_struct_3A;
    BYTE byte_A9E170[] = {0x80, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01};

    DWORD dwOpenFlags = 0;
    ha = ha;

    if (pBetTable != NULL)
    {
        GetFileBlockEntry_BetData(pBetTable, dwBlockIndex, &BlockEntry);
/*
        if (dwOpenFlags & 0x80)
        {
            BlockEntry.result32 = pParsedBetData->field_74[dwBlockIndex];
        }

        if (dwOpenFlags & 0x40)
        {
            INT128 result128 = pParsedBetData->field_8C[dwBlockIndex];

            BlockEntry.result128_1 = result128.dw1;
            BlockEntry.result128_2 = result128.dw2;
            BlockEntry.result128_3 = result128.dw3;
            BlockEntry.result128_4 = result128.dw4;
        }

        if (dwOpenFlags & 0x100)
        {
            INT64 result64 = pParsedBetData->field_5C[dwBlockIndex];

            BlockEntry.result64_hi = (DWORD)(result64 >> 0x20);
            BlockEntry.result64_lo = (DWORD)(result64 & 0xFFFFFFFF);
        }

        if (dwOpenFlags & 0x1000)
        {
            BYTE BitMask = byte_A9E170[dwBlockIndex & 0x07];

            BlockEntry.field_38 = (pParsedBetData->field_A4[dwBlockIndex / 8] & BitMask) ? 0x100 : 0;
        }
*/

        // 0x3A bytes !!!
        memcpy(pBlockEntry, &BlockEntry, sizeof(MPQ_FILE_BLOCK_ENTRY));
    }
}

//-----------------------------------------------------------------------------
// Support for opening files

#ifdef __STORMLIB_TEST__
void TestNewHashBlockTables(TMPQArchive * ha)
{
    if (ha->pHetTable != NULL && ha->pBetTable != NULL)
    {
        SFILE_FIND_DATA sf;
        HANDLE hFind;
        bool bResult = 1;

        hFind = SFileFindFirstFile((HANDLE)ha, "*", &sf, NULL);
        while (hFind && bResult)
        {
            MPQ_FILE_BLOCK_ENTRY BlockEntry;
            TFileEntry * pFileEntry;
            DWORD dwBlockIndex;

            pFileEntry = GetFileEntry_HetBet(ha, sf.cFileName);
            dwBlockIndex = (DWORD)(pFileEntry - ha->pFileTable);

            assert(dwBlockIndex == sf.dwBlockIndex);
            assert(pFileEntry != NULL);

            GetFileBlockEntry(ha, ha->pBetTable, &BlockEntry, dwBlockIndex);
            assert(pFileEntry->ByteOffset == BlockEntry.dwFilePosLo);
            assert(pFileEntry->dwFileSize == BlockEntry.dwFileSizeLo);
            assert(pFileEntry->dwCmpSize  == BlockEntry.dwCmpSizeLo);
            assert(pFileEntry->dwFlags    == BlockEntry.dwFlags);

            bResult = SFileFindNextFile(hFind, &sf);
        }
    }
}
#endif