/*****************************************************************************/
/* StormLib.h                        Copyright (c) Ladislav Zezula 1999-2010 */
/*---------------------------------------------------------------------------*/
/* StormLib library v 7.02                                                   */
/*                                                                           */
/* Author : Ladislav Zezula                                                  */
/* E-mail : ladik@zezula.net                                                 */
/* WWW    : http://www.zezula.net                                            */
/*---------------------------------------------------------------------------*/
/*   Date    Ver   Who  Comment                                              */
/* --------  ----  ---  -------                                              */
/* xx.xx.99  1.00  Lad  Created                                              */
/* 24.03.03  2.50  Lad  Version 2.50                                         */
/* 02.04.03  3.00  Lad  Version 3.00 with compression                        */
/* 11.04.03  3.01  Lad  Renamed to StormLib.h for compatibility with         */
/*                      original headers for Storm.dll                       */
/* 10.05.03  3.02  Lad  Added Pkware DCL compression                         */
/* 26.05.03  4.00  Lad  Completed all compressions                           */
/* 18.06.03  4.01  Lad  Added SFileSetFileLocale                             */
/*                      Added SFileExtractFile                               */
/* 26.07.03  4.02  Lad  Implemented nameless rename and delete               */
/* 26.07.03  4.03  Lad  Added support for protected MPQs                     */
/* 28.08.03  4.10  Lad  Fixed bugs that caused StormLib incorrectly work     */
/*                      with Diablo I savegames and with files having full   */
/*                      hash table                                           */
/* 08.12.03  4.11  DCH  Fixed bug in reading file sector larger than 0x1000  */
/*                      on certain files.                                    */
/*                      Fixed bug in AddFile with MPQ_FILE_REPLACE_EXISTING  */
/*                      (Thanx Daniel Chiamarello, dchiamarello@madvawes.com)*/
/* 21.12.03  4.50  Lad  Completed port for Mac                               */
/*                      Fixed bug in compacting (if fsize is mul of 0x1000)  */
/*                      Fixed bug in SCompCompress                           */
/* 27.05.04  4.51  Lad  Changed memory management from new/delete to our     */
/*                      own macros                                           */
/* 22.06.04  4.60  Lad  Optimized search. Support for multiple listfiles.    */
/* 30.09.04  4.61  Lad  Fixed some bugs (Aaargh !!!)                         */
/*                      Correctly works if HashTableSize > BlockTableSize    */
/* 29.12.04  4.70  Lad  Fixed compatibility problem with MPQs from WoW       */
/* 14.07.05  5.00  Lad  Added the BZLIB compression support                  */
/*                      Added suport of files stored as single unit          */
/* 17.04.06  5.01  Lad  Converted to MS Visual Studio 8.0                    */
/*                      Fixed issue with protected Warcraft 3 protected maps */
/* 15.05.06  5.02  Lad  Fixed issue with WoW 1.10+                           */
/* 07.09.06  5.10  Lad  Fixed processing files longer than 2GB               */
/* 22.11.06  6.00  Lad  Support for MPQ archives V2                          */
/* 12.06.07  6.10  Lad  Support for (attributes) file                        */
/* 10.09.07  6.12  Lad  Support for MPQs protected by corrupting hash table  */
/* 03.12.07  6.13  Lad  Support for MPQs with hash tbl size > block tbl size */
/* 07.04.08  6.20  Lad  Added SFileFlushArchive                              */
/* 09.04.08        Lad  Removed FilePointer variable from MPQ handle         */
/*                      structure, as it caused more problems than benefits  */
/* 12.05.08  6.22  Lad  Support for w3xMaster map protector                  */
/* 05.10.08  6.23  Lad  Support for protectors who set negative values in    */
/*                      the table of file blocks                             */
/* 26.05.09  6.24  Lad  Fixed search for multiple lang files with deleted    */
/*                      entries                                              */
/* 03.09.09  6.25  Lad  Fixed decompression bug in huffmann decompression    */
/* 22.03.10  6.50  Lad  New compressions in Starcraft II (LZMA, sparse)      */
/*                      Fixed compacting MPQs that contain single unit files */
/* 26.04.10  7.00  Lad  Major rewrite                                        */
/* 08.06.10  7.10  Lad  Support for partial MPQs                             */
/* 08.07.10  7.11  Lad  Support for MPQs v 3.0                               */
/* 20.08.10  7.20  Lad  Support for opening multiple MPQs in patch mode      */
/* 20.09.10  8.00  Lad  MPQs v 4.0, HET and BET tables                       */
/*****************************************************************************/

#ifndef __STORMLIB_H_
#define __STORMLIB_H_

#ifdef _MSC_VER
#pragma warning(disable:4668)       // 'XXX' is not defined as a preprocessor macro, replacing with '0' for '#if/#elif'
#pragma warning(disable:4820)       // 'XXX' : '2' bytes padding added after data member 'XXX::yyy'
#endif

#include "StormPort.h"

//-----------------------------------------------------------------------------
// Use the apropriate library
//
// The library type is encoded in the library name as the following
// StormLibXYZ.lib
//
//  X - D for Debug version, R for Release version
//  Y - A for ANSI version, U for Unicode version (Unicode version does not exist yet)
//  Z - S for static C library, D for multithreaded DLL C-library
//

#if defined(_MSC_VER) && !defined (__STORMLIB_SELF__)
  #ifdef _DEBUG                                 // DEBUG VERSIONS
    #ifdef _DLL
      #pragma comment(lib, "StormLibDAD.lib")   // Debug Ansi Dynamic version
    #else
      #pragma comment(lib, "StormLibDAS.lib")   // Debug Ansi Static version
    #endif
  #else                                         // RELEASE VERSIONS
    #ifdef _DLL
      #pragma comment(lib, "StormLibRAD.lib")   // Release Ansi Dynamic version
    #else
      #pragma comment(lib, "StormLibRAS.lib")   // Release Ansi Static version
    #endif
  #endif
#endif

//-----------------------------------------------------------------------------
// Defines

#define ID_MPQ                   0x1A51504D // MPQ archive header ID ('MPQ\x1A')
#define ID_MPQ_USERDATA          0x1B51504D // MPQ userdata entry ('MPQ\x1B')

#define ERROR_AVI_FILE                10000 // No MPQ file, but AVI file.
#define ERROR_UNKNOWN_FILE_KEY        10001 // Returned by SFileReadFile when can't find file key
#define ERROR_CHECKSUM_ERROR          10002 // Returned by SFileReadFile when sector CRC doesn't match
#define ERROR_INTERNAL_FILE           10003 // The givn operation is not allowed on internal file

// Values for SFileCreateArchive
#define HASH_TABLE_SIZE_MIN      0x00000004 // Minimum acceptable hash size
#define HASH_TABLE_SIZE_MAX      0x00080000 // Maximum acceptable hash size

#define HASH_ENTRY_DELETED       0xFFFFFFFE // Block index for deleted hash entry
#define HASH_ENTRY_FREE          0xFFFFFFFF // Block index for free hash entry

#define HASH_STATE_SIZE                0x60 // Size of LibTomCrypt's hash_state structure

#define MPQ_PATCH_PREFIX_LEN           0x20 // Maximum length of the patch prefix

// Values for TFileStream::Flags
#define STREAM_FLAG_READ_ONLY          0x01 // The stream is read only
#define STREAM_FLAG_PART_FILE          0x02 // The stream is a PART file.
#define STREAM_FLAG_ENCRYPTED_FILE     0x04 // The stream is an encrypted MPQ (MPQE).

// Values for SFileOpenArchive
#define SFILE_OPEN_HARD_DISK_FILE         2 // Open the archive on HDD
#define SFILE_OPEN_CDROM_FILE             3 // Open the archive only if it is on CDROM

// Values for SFileOpenFile
#define SFILE_OPEN_FROM_MPQ      0x00000000 // Open the file from the MPQ archive
#define SFILE_OPEN_PATCHED_FILE  0x00000001 // Open the file from the MPQ archive
#define SFILE_OPEN_BY_INDEX      0x00000002 // The 'szFileName' parameter is actually the file index
#define SFILE_OPEN_ANY_LOCALE    0xFFFFFFFE // Reserved for StormLib internal use
#define SFILE_OPEN_LOCAL_FILE    0xFFFFFFFF // Open the file from the MPQ archive

// Flags for TMPQArchive::dwFlags
#define MPQ_FLAG_READ_ONLY       0x00000001 // If set, the MPQ has been open for read-only access
#define MPQ_FLAG_NO_HEADER       0x00000002 // The MPQ header was not written yet
#define MPQ_FLAG_CHANGED         0x00000004 // If set, the MPQ tables have been changed
#define MPQ_FLAG_PROTECTED       0x00000008 // Set on protected MPQs (like W3M maps)
#define MPQ_FLAG_CHECK_SECTOR_CRC 0x00000010 // Checking sector CRC when reading files
#define MPQ_FLAG_NEED_FIX_SIZE   0x00000020 // Used during opening the archive

// Return value for SFilGetFileSize and SFileSetFilePointer
#define SFILE_INVALID_SIZE       0xFFFFFFFF
#define SFILE_INVALID_POS        0xFFFFFFFF
#define SFILE_INVALID_ATTRIBUTES 0xFFFFFFFF

// Flags for SFileAddFile
#define MPQ_FILE_IMPLODE         0x00000100 // Implode method (By PKWARE Data Compression Library)
#define MPQ_FILE_COMPRESS        0x00000200 // Compress methods (By multiple methods)
#define MPQ_FILE_COMPRESSED      0x0000FF00 // File is compressed
#define MPQ_FILE_ENCRYPTED       0x00010000 // Indicates whether file is encrypted
#define MPQ_FILE_FIX_KEY         0x00020000 // File decryption key has to be fixed
#define MPQ_FILE_PATCH_FILE      0x00100000 // The file is a patch file. Raw file data begin with TPatchInfo structure
#define MPQ_FILE_SINGLE_UNIT     0x01000000 // File is stored as a single unit, rather than split into sectors (Thx, Quantam)
#define MPQ_FILE_DELETE_MARKER   0x02000000 // File is a deletion marker, indicating that the file no longer exists.
                                            // The file is only 1 byte long and its name is a hash
#define MPQ_FILE_SECTOR_CRC      0x04000000 // File has checksums for each sector.
                                            // Ignored if file is not compressed or imploded.
#define MPQ_FILE_EXISTS          0x80000000 // Set if file exists, reset when the file was deleted
#define MPQ_FILE_REPLACEEXISTING 0x80000000 // Replace when the file exist (SFileAddFile)

#define MPQ_FILE_VALID_FLAGS     (MPQ_FILE_IMPLODE       |  \
                                  MPQ_FILE_COMPRESS      |  \
                                  MPQ_FILE_ENCRYPTED     |  \
                                  MPQ_FILE_FIX_KEY       |  \
                                  MPQ_FILE_PATCH_FILE    |  \
                                  MPQ_FILE_SINGLE_UNIT   |  \
                                  MPQ_FILE_DELETE_MARKER |  \
                                  MPQ_FILE_SECTOR_CRC    |  \
                                  MPQ_FILE_EXISTS)

// Compression types for multiple compressions
#define MPQ_COMPRESSION_HUFFMANN       0x01 // Huffmann compression (used on WAVE files only)
#define MPQ_COMPRESSION_ZLIB           0x02 // ZLIB compression
#define MPQ_COMPRESSION_PKWARE         0x08 // PKWARE DCL compression
#define MPQ_COMPRESSION_BZIP2          0x10 // BZIP2 compression (added in Warcraft III)
#define MPQ_COMPRESSION_SPARSE         0x20 // Sparse compression (added in Starcraft 2)
#define MPQ_COMPRESSION_ADPCM_MONO     0x40 // IMA ADPCM compression (mono)
#define MPQ_COMPRESSION_ADPCM_STEREO   0x80 // IMA ADPCM compression (stereo)

// For backward compatibility
#define MPQ_COMPRESSION_WAVE_MONO      0x40 // IMA ADPCM compression (mono)
#define MPQ_COMPRESSION_WAVE_STEREO    0x80 // IMA ADPCM compression (stereo)

// LZMA compression. Added in Starcraft 2. This value is NOT a combination of flags.
#define MPQ_COMPRESSION_LZMA           0x12

// Constants for SFileAddWave
#define MPQ_WAVE_QUALITY_HIGH        0      // Best quality, the worst compression
#define MPQ_WAVE_QUALITY_MEDIUM      1      // Medium quality, medium compression
#define MPQ_WAVE_QUALITY_LOW         2      // Low quality, the best compression

// Constants for SFileGetFileInfo
#define SFILE_INFO_ARCHIVE_NAME      1      // MPQ size (value from header)
#define SFILE_INFO_ARCHIVE_SIZE      2      // MPQ size (value from header)
#define SFILE_INFO_HASH_TABLE_SIZE   3      // Size of hash table, in entries
#define SFILE_INFO_BLOCK_TABLE_SIZE  4      // Number of entries in the block table
#define SFILE_INFO_SECTOR_SIZE       5      // Size of file sector (in bytes)
#define SFILE_INFO_HASH_TABLE        6      // Pointer to Hash table (TMPQHash *)
#define SFILE_INFO_BLOCK_TABLE       7      // Pointer to Block Table (TMPQBlock *)
#define SFILE_INFO_NUM_FILES         8      // Real number of files within archive
#define SFILE_INFO_STREAM_FLAGS      9      // Stream flags for the MPQ. See STREAM_FLAG_XXX
#define SFILE_INFO_IS_READ_ONLY     10      // TRUE of the MPQ was open as read only
//------
#define SFILE_INFO_HASH_INDEX      100      // Hash index of file in MPQ
#define SFILE_INFO_CODENAME1       101      // The first codename of the file
#define SFILE_INFO_CODENAME2       102      // The second codename of the file
#define SFILE_INFO_LOCALEID        103      // Locale ID of file in MPQ
#define SFILE_INFO_BLOCKINDEX      104      // Index to Block Table
#define SFILE_INFO_FILE_SIZE       105      // Original file size (from the block table)
#define SFILE_INFO_COMPRESSED_SIZE 106      // Compressed file size (from the block table)
#define SFILE_INFO_FLAGS           107      // File flags
#define SFILE_INFO_POSITION        108      // File position within archive
#define SFILE_INFO_KEY             109      // File decryption key
#define SFILE_INFO_KEY_UNFIXED     110      // Decryption key not fixed to file pos and size
#define SFILE_INFO_FILETIME        111      // TMPQFileTime

#define LISTFILE_NAME          "(listfile)" // Name of internal listfile
#define SIGNATURE_NAME        "(signature)" // Name of internal signature
#define ATTRIBUTES_NAME      "(attributes)" // Name of internal attributes file

#define STORMLIB_VERSION             0x0800 // Current version of StormLib (8.00)
#define STORMLIB_VERSION_STRING      "8.00"

#define MPQ_FORMAT_VERSION_1              0 // Up to The Burning Crusade
#define MPQ_FORMAT_VERSION_2              1 // The Burning Crusade and newer
#define MPQ_FORMAT_VERSION_3              2 // WoW Cataclysm Beta and newer
#define MPQ_FORMAT_VERSION_4              3 // WoW Cataclysm Beta and newer

// Flags for MPQ attributes
#define MPQ_ATTRIBUTE_CRC32      0x00000001 // The "(attributes)" contains CRC32 for each file
#define MPQ_ATTRIBUTE_FILETIME   0x00000002 // The "(attributes)" contains file time for each file
#define MPQ_ATTRIBUTE_MD5        0x00000004 // The "(attributes)" contains MD5 for each file
#define MPQ_ATTRIBUTE_ALL        0x00000007 // Summary mask

#define MPQ_ATTRIBUTES_V1               100 // (attributes) format version 1.00

// Flags for SFileOpenArchive
#define MPQ_OPEN_NO_LISTFILE         0x0010 // Don't load the internal listfile
#define MPQ_OPEN_NO_ATTRIBUTES       0x0020 // Don't open the attributes
#define MPQ_OPEN_FORCE_MPQ_V1        0x0040 // Always open the archive as MPQ v 1.00, ignore the "wFormatVersion" variable in the header
#define MPQ_OPEN_CHECK_SECTOR_CRC    0x0080 // On files with MPQ_FILE_SECTOR_CRC, the CRC will be checked when reading file
#define MPQ_OPEN_READ_ONLY           0x0100 // Open the archive for read-only access
#define MPQ_OPEN_ENCRYPTED           0x0200 // Opens an encrypted MPQ archive (Example: Starcraft II installation)

// Flags for SFileCreateArchive
#define MPQ_CREATE_ATTRIBUTES    0x00000001 // Also add the (attributes) file
#define MPQ_CREATE_NO_MPQ_CHECK  0x00000002 // Used internally by StormLib
#define MPQ_CREATE_ARCHIVE_V1    0x00000000 // Creates archive of version 1.0 (size up to 4GB)
#define MPQ_CREATE_ARCHIVE_V2    0x00010000 // Creates archive of version 2.0 (larger than 4 GB)
#define MPQ_CREATE_ARCHIVE_V3    0x00020000 // Creates archive of version 3.0
#define MPQ_CREATE_ARCHIVE_V4    0x00030000 // Creates archive of version 4.0
#define MPQ_CREATE_ARCHIVE_VMASK 0x000F0000 // Mask for archive version

// Return values for SFileVerifyFile
#define VERIFY_OPEN_ERROR            0x0001 // Failed to open the file
#define VERIFY_READ_ERROR            0x0002 // Failed to read all data from the file
#define VERIFY_SECTORS_HAVE_CHECKSUM 0x0004 // Sector checksum is available for the file
#define VERIFY_SECTOR_CHECKSUM_ERROR 0x0008 // Sector checksum doesn't match
#define VERIFY_FILE_HAS_CHECKSUM     0x0010 // File CRC32 is available for the file
#define VERIFY_FILE_CHECKSUM_ERROR   0x0020 // File CRC32 doesn't match
#define VERIFY_FILE_HAS_MD5          0x0040 // File MD5 is available for the file
#define VERIFY_FILE_MD5_ERROR        0x0080 // File MD5 doesn't match

// Flags for SFileVerifyRawData (for MPQs version 4.0 or higher)
#define SFILE_VERIFY_MPQ_HEADER      0x0001 // Verify raw MPQ header
#define SFILE_VERIFY_HET_TABLE       0x0002 // Verify raw data of the HET table
#define SFILE_VERIFY_BET_TABLE       0x0003 // Verify raw data of the BET table
#define SFILE_VERIFY_HASH_TABLE      0x0004 // Verify raw data of the hash table
#define SFILE_VERIFY_BLOCK_TABLE     0x0005 // Verify raw data of the block table
#define SFILE_VERIFY_HIBLOCK_TABLE   0x0006 // Verify raw data of the hi-block table
#define SFILE_VERIFY_FILE            0x0007 // Verify raw data of a file

// Return values for SFileVerifyArchive
#define ERROR_NO_SIGNATURE                0 // There is no signature in the MPQ
#define ERROR_VERIFY_FAILED               1 // There was an error during verifying signature (like no memory)
#define ERROR_WEAK_SIGNATURE_OK           2 // There is a weak signature and sign check passed
#define ERROR_WEAK_SIGNATURE_ERROR        3 // There is a weak signature but sign check failed
#define ERROR_STRONG_SIGNATURE_OK         4 // There is a strong signature and sign check passed
#define ERROR_STRONG_SIGNATURE_ERROR      5 // There is a strong signature but sign check failed

#ifndef MD5_DIGEST_SIZE
#define MD5_DIGEST_SIZE             0x10
#endif

#ifndef SHA1_DIGEST_SIZE
#define SHA1_DIGEST_SIZE            0x14    // 160 bits
#endif

#ifndef LANG_NEUTRAL
#define LANG_NEUTRAL                0x00    // Neutral locale
#endif

//-----------------------------------------------------------------------------
// Callback functions

// Values for compact callback
#define CCB_CHECKING_FILES                1 // Checking archive (dwParam1 = current, dwParam2 = total)
#define CCB_CHECKING_HASH_TABLE           2 // Checking hash table (dwParam1 = current, dwParam2 = total)
#define CCB_COPYING_NON_MPQ_DATA          3 // Copying non-MPQ data: No params used
#define CCB_COMPACTING_FILES              4 // Compacting archive (dwParam1 = current, dwParam2 = total)
#define CCB_CLOSING_ARCHIVE               5 // Closing archive: No params used

typedef void (WINAPI * SFILE_ADDFILE_CALLBACK)(void * pvUserData, DWORD dwBytesWritten, DWORD dwTotalBytes, bool bFinalCall);
typedef void (WINAPI * SFILE_COMPACT_CALLBACK)(void * pvUserData, DWORD dwWorkType, ULONGLONG BytesProcessed, ULONGLONG TotalBytes);

//-----------------------------------------------------------------------------
// Stream support - structures

struct TFileStream;

typedef bool (*STREAM_GETPOS)(
    TFileStream * pStream,             // Pointer to an open stream
    ULONGLONG & ByteOffset              // Pointer to store current file position
    );

typedef bool (*STREAM_READ)(
    TFileStream * pStream,             // Pointer to an open stream
    ULONGLONG * pByteOffset,           // Pointer to file byte offset. If NULL, it reads from the current position
    void * pvBuffer,                   // Pointer to data to be read
    DWORD dwBytesToRead                 // Number of bytes to read from the file
    );

typedef bool (*STREAM_WRITE)(
    TFileStream * pStream,             // Pointer to an open stream
    ULONGLONG * pByteOffset,           // Pointer to file byte offset. If NULL, it writes to the current position
    const void * pvBuffer,             // Pointer to data to be written
    DWORD dwBytesToWrite                // Number of bytes to read from the file
    );

typedef bool (*STREAM_GETSIZE)(
    TFileStream * pStream,             // Pointer to an open stream
    ULONGLONG & FileSize                // Receives the file size, in bytes
    );

typedef bool (*STREAM_SETSIZE)(
    TFileStream * pStream,             // Pointer to an open stream
    ULONGLONG FileSize                  // New size for the file, in bytes
    );

// Common stream structure. Can be variable length
struct TFileStream
{
    ULONGLONG      RawFilePos;          // Current position in raw file
    HANDLE         hFile;               // File handle. Do not use directly.
    char           szFileName[MAX_PATH];// Name of the file
    BYTE           StreamFlags;         // See STREAM_FLAG_XXXX

    STREAM_GETPOS  StreamGetPos;        // Pointer to function that returns current file position
    STREAM_READ    StreamRead;          // Pointer to stream read function for this archive. Do not use directly.
    STREAM_WRITE   StreamWrite;         // Pointer to stream write function for this archive. Do not use directly.
    STREAM_GETSIZE StreamGetSize;       // Pointer to function returning file size
    STREAM_SETSIZE StreamSetSize;       // Pointer to function changing file size

    // Extra members may follow
};

//-----------------------------------------------------------------------------
// Structures

#define MPQ_HEADER_SIZE_V1    0x20
#define MPQ_HEADER_SIZE_V2    0x2C
#define MPQ_HEADER_SIZE_V3    0x44
#define MPQ_HEADER_SIZE_V4    0xD0

struct TMPQUserData
{
    // The ID_MPQ_USERDATA ('MPQ\x1B') signature
    DWORD dwID;

    // Maximum size of the user data
    DWORD cbUserDataSize;

    // Offset of the MPQ header, relative to the begin of this header
    DWORD dwHeaderOffs;

    // Appears to be size of user data header (Starcraft II maps)
    DWORD cbUserDataHeader;
};

// MPQ file header
//
// We have to make sure that the header is packed OK.
// Reason: A 64-bit integer at the beginning of 3.0 part,
// which is offset 0x2C
#pragma pack(push, 1)
struct TMPQHeader
{
    // The ID_MPQ ('MPQ\x1A') signature
    DWORD dwID;

    // Size of the archive header
    DWORD dwHeaderSize;

    // 32-bit size of MPQ archive
    // This field is deprecated in the Burning Crusade MoPaQ format, and the size of the archive
    // is calculated as the size from the beginning of the archive to the end of the hash table,
    // block table, or hi-block table (whichever is largest).
    DWORD dwArchiveSize;

    // 0 = Format 1.0 (up to The Burning Crusade)
    // 1 = Format 2.0 (The Burning Crusade and newer)
    // 2 = Format 3.0 (WoW - Cataclysm beta or newer)
    USHORT wFormatVersion;

    // Power of two exponent specifying the number of 512-byte disk sectors in each file sector
    // in the archive. The size of each file sector in the archive is 512 * 2 ^ wSectorSize.
    // Bugs in the Storm library dictate that this should always be 3 (4096 byte sectors).
    USHORT wSectorSize;

    // Offset to the beginning of the hash table, relative to the beginning of the archive.
    DWORD dwHashTablePos;

    // Offset to the beginning of the block table, relative to the beginning of the archive.
    DWORD dwBlockTablePos;

    // Number of entries in the hash table. Must be a power of two, and must be less than 2^16 for
    // the original MoPaQ format, or less than 2^20 for the Burning Crusade format.
    DWORD dwHashTableSize;

    // Number of entries in the block table
    DWORD dwBlockTableSize;

    //-- MPQ HEADER v 2.0 -------------------------------------------

    // Offset to the beginning of array of 16-bit high parts of file offsets.
    ULONGLONG HiBlockTablePos64;

    // High 16 bits of the hash table offset for large archives.
    USHORT wHashTablePosHi;

    // High 16 bits of the block table offset for large archives.
    USHORT wBlockTablePosHi;

    //-- MPQ HEADER v 3.0 -------------------------------------------

    // 64-bit version of the archive size
    ULONGLONG ArchiveSize64;

    // 64-bit position of the BET table
    ULONGLONG BetTablePos64;

    // 64-bit position of the HET table
    ULONGLONG HetTablePos64;

    //-- MPQ HEADER v 4.0 -------------------------------------------

    // Compressed size of the hash table
    ULONGLONG HashTableSize64;

    // Compressed size of the block table
    ULONGLONG BlockTableSize64;

    // Compressed size of the hi-block table
    ULONGLONG HiBlockTableSize64;

    // Compressed size of the HET block
    ULONGLONG HetTableSize64;

    // Compressed size of the BET block
    ULONGLONG BetTableSize64;

    // Size of raw data chunk to calculate MD5.
    // MD5 of each data chunk follows the raw file data.
    DWORD dwRawChunkSize;

    // Array of MD5's
    unsigned char MD5_BlockTable[MD5_DIGEST_SIZE];      // MD5 of the block table before decryption
    unsigned char MD5_HashTable[MD5_DIGEST_SIZE];       // MD5 of the hash table before decryption
    unsigned char MD5_HiBlockTable[MD5_DIGEST_SIZE];    // MD5 of the hi-block table
    unsigned char MD5_UnknownA0[MD5_DIGEST_SIZE];       // Most likely not a MD5
    unsigned char MD5_UnknownB0[MD5_DIGEST_SIZE];       // Most likely not a MD5
    unsigned char MD5_MpqHeader[MD5_DIGEST_SIZE];       // MD5 of the MPQ header from signature to (including) MD5_UnknownB0
};
#pragma pack(pop)

// Hash entry. All files in the archive are searched by their hashes.
struct TMPQHash
{
    // The hash of the file path, using method A.
    DWORD dwName1;

    // The hash of the file path, using method B.
    DWORD dwName2;

#ifdef PLATFORM_LITTLE_ENDIAN

    // The language of the file. This is a Windows LANGID data type, and uses the same values.
    // 0 indicates the default language (American English), or that the file is language-neutral.
    USHORT lcLocale;

    // The platform the file is used for. 0 indicates the default platform.
    // No other values have been observed.
    // Note: wPlatform is actually just BYTE, but since it has never been used, we don't care.
    USHORT wPlatform;

#else

    USHORT wPlatform;
    USHORT lcLocale;

#endif

    // If the hash table entry is valid, this is the index into the block table of the file.
    // Otherwise, one of the following two values:
    //  - FFFFFFFFh: Hash table entry is empty, and has always been empty.
    //               Terminates searches for a given file.
    //  - FFFFFFFEh: Hash table entry is empty, but was valid at some point (a deleted file).
    //               Does not terminate searches for a given file.
    DWORD dwBlockIndex;
};

// File description block contains informations about the file
struct TMPQBlock
{
    // Offset of the beginning of the file, relative to the beginning of the archive.
    DWORD dwFilePos;

    // Compressed file size
    DWORD dwCSize;

    // Only valid if the block is a file; otherwise meaningless, and should be 0.
    // If the file is compressed, this is the size of the uncompressed file data.
    DWORD dwFSize;

    // Flags for the file. See MPQ_FILE_XXXX constants
    DWORD dwFlags;
};

// Patch file information, preceding the sector offset table
struct TPatchInfo
{
	DWORD dwLength;                     // Length of patch info header, in bytes
	DWORD dwFlags;                      // Flags. 0x80000000 = MD5 (?)
	DWORD dwDataSize;                   // Uncompressed size of the patch file
	BYTE  md5[0x10];                    // MD5 of the entire patch file after decompression

    // Followed by the sector table (variable length)
};

// Header for PTCH files
struct TPatchHeader
{
    //-- PATCH header -----------------------------------
    DWORD dwSignature;                  // 'PTCH'
    DWORD dwSizeOfPatchData;            // Size of the entire patch (decompressed)
    DWORD dwSizeBeforePatch;            // Size of the file before patch
    DWORD dwSizeAfterPatch;             // Size of file after patch

    //-- MD5 block --------------------------------------
    DWORD dwMD5;                        // 'MD5_'
    DWORD dwMd5BlockSize;               // Size of the MD5 block, including the signature and size itself
    BYTE md5_before_patch[0x10];        // MD5 of the original (unpached) file
    BYTE md5_after_patch[0x10];         // MD5 of the patched file

    //-- XFRM block -------------------------------------
    DWORD dwXFRM;                       // 'XFRM'
    DWORD dwXfrmBlockSize;              // Size of the XFRM block, includes XFRM header and patch data
    DWORD dwPatchType;                  // Type of patch ('BSD0' or 'COPY')

    // Followed by the patch data
};

#define SIZE_OF_XFRM_HEADER  0x0C

// This is the combined file entry for maintaining file list in the MPQ.
// This structure is combined from block table, hi-block table,
// (attributes) file and from (listfile).
struct TFileEntry
{
    ULONGLONG ByteOffset;               // Position of the file content in the MPQ, relative to the MPQ header
    ULONGLONG FileTime;                 // FileTime from the (attributes) file. 0 if not present.
    DWORD     dwHashIndex;              // Index in the hash table
    DWORD     dwFileSize;               // Decompressed size of the file
    DWORD     dwCmpSize;                // Compressed size of the file (i.e., size of the file data in the MPQ)
    DWORD     dwFlags;                  // File flags (from block table)
    USHORT    lcLocale;                 // Locale ID for the file
    USHORT    wPlatform;                // Platform ID for the file
    DWORD     dwCrc32;                  // CRC32 from (attributes) file. 0 if not present.
    unsigned char md5[MD5_DIGEST_SIZE]; // File MD5 from the (attributes) file. 0 if not present.
    char * szFileName;                  // File name. NULL if not known.
};

// Archive handle structure
struct TMPQHetTable;
struct TMPQBetTable;
struct TMPQArchive
{
    TFileStream  * pStream;             // Open stream for the MPQ

    ULONGLONG      UserDataPos;         // Position of user data (relative to the begin of the file)
    ULONGLONG      MpqPos;              // MPQ header offset (relative to the begin of the file)

    TMPQArchive  * haPatch;             // Pointer to patch archive, if any
    char szPatchPrefix[MPQ_PATCH_PREFIX_LEN]; // Prefix for file names in patch MPQs

    TMPQUserData * pUserData;           // MPQ user data (NULL if not present in the file)
    TMPQHeader   * pHeader;             // MPQ file header
    TMPQHash     * pHashTable;          // Hash table
    TFileEntry   * pFileTable;          // File table
    TMPQHetTable * pHetTable;           // Het table
    TMPQBetTable * pBetTable;           // Bet table

    TMPQUserData   UserData;            // MPQ user data. Valid only when ID_MPQ_USERDATA has been found
    BYTE           HeaderData[MPQ_HEADER_SIZE_V4];  // Storage for MPQ header

    DWORD          dwHETBlockSize;
    DWORD          dwBETBlockSize;
    DWORD          dwFileTableSize;     // Size of the file table
    DWORD          dwFileTableMax;      // Maximum size of the file table
    DWORD          dwSectorSize;        // Default size of one file sector
    DWORD          dwAttrFlags;         // Flags for the (attributes) file
    DWORD          dwFlags;             // See MPQ_FLAG_XXXXX
};

// File handle structure
struct TMPQFile
{
    TFileStream  * pStream;             // File stream. Only used on local files
    TMPQArchive  * ha;                  // Archive handle
    TFileEntry   * pFileEntry;          // File entry for the file
    DWORD          dwFileKey;           // Decryption key
    DWORD          dwFilePos;           // Current file position
    ULONGLONG      RawFilePos;          // Offset in MPQ archive (relative to file begin)
    ULONGLONG      MpqFilePos;          // Offset in MPQ archive (relative to MPQ header)
    DWORD          dwMagic;             // 'FILE'

    TMPQFile     * hfPatchFile;         // Pointer to open patch file
    TPatchHeader * pPatchHeader;        // Patch header. Only used if the file is a patch file
    LPBYTE         pbFileData;          // Loaded and patched file data. Only used if the file is a patch file
    DWORD          cbFileData;          // Size of loaded patched data

    TPatchInfo   * PatchInfo;           // Patch info block, preceding the sector table
	DWORD        * SectorOffsets;       // Position of each file sector, relative to the begin of the file. Only for compressed files.
    DWORD        * SectorChksums;       // Array of ADLER32 values for each sector
    DWORD          dwDataSectors;       // Number of data sectors in the file
    DWORD          dwSectorCount;       // Number of entries in the sector offset table
    DWORD          dwPatchedFileSize;   // Size of patched file. Used when saving patch file to the MPQ
    DWORD          dwDataSize;          // Size of data in the file (on patch files, this differs from file size in block table entry)

    LPBYTE         pbFileSector;        // Last loaded file sector. For single unit files, entire file content
    DWORD          dwSectorOffs;        // File position of currently loaded file sector
    DWORD          dwSectorSize;        // Size of the file sector. For single unit files, this is equal to the file size

    unsigned char  hctx[HASH_STATE_SIZE];// Hash state for MD5. Used when saving file to MPQ
    DWORD          dwCrc32;             // CRC32 value, used when saving file to MPQ

    DWORD          dwHashIndex;         // Index to Hash table
    DWORD          dwBlockIndex;        // Index to Block table
    bool           bCheckSectorCRCs;    // If true, then SFileReadFile will check sector CRCs when reading the file
    bool           bIsWriteHandle;      // If true, this handle has been created by SFileCreateFile
    bool           bErrorOccured;       // If true, then at least one error occured during saving the file to the archive
};

typedef struct _SFILE_FIND_DATA
{
    char   cFileName[MAX_PATH];         // Full name of the found file
    char * szPlainName;                 // Plain name of the found file
    DWORD  dwHashIndex;                 // Hash table index for the file
    DWORD  dwBlockIndex;                // Block table index for the file
    DWORD  dwFileSize;                  // File size in bytes
    DWORD  dwFileFlags;                 // MPQ file flags
    DWORD  dwCompSize;                  // Compressed file size
    DWORD  dwFileTimeLo;                // Low 32-bits of the file time (0 if not present)
    DWORD  dwFileTimeHi;                // High 32-bits of the file time (0 if not present)
    LCID   lcLocale;                    // Locale version
} SFILE_FIND_DATA, *PSFILE_FIND_DATA;

//-----------------------------------------------------------------------------
// Memory management
//
// We use our own macros for allocating/freeing memory. If you want
// to redefine them, please keep the following rules
//
//  - The memory allocation must return NULL if not enough memory
//    (i.e not to throw exception)
//  - It is not necessary to fill the allocated buffer with zeros
//  - Memory freeing function doesn't have to test the pointer to NULL.
//

#if defined(_MSC_VER) && defined(_DEBUG)
__inline void * DebugMalloc(char * /* szFile */, int /* nLine */, size_t nSize)
{
//  return new BYTE[nSize];
    return HeapAlloc(GetProcessHeap(), 0, nSize);
}

__inline void DebugFree(void * ptr)
{
//  delete [] ptr;
    HeapFree(GetProcessHeap(), 0, ptr);
}

#define ALLOCMEM(type, nitems) (type *)DebugMalloc(__FILE__, __LINE__, (nitems) * sizeof(type))
#define FREEMEM(ptr)           DebugFree(ptr)
#else

#define ALLOCMEM(type, nitems)   (type *)malloc((nitems) * sizeof(type))
#define FREEMEM(ptr) free(ptr)

#endif

//-----------------------------------------------------------------------------
// Stream support - functions

TFileStream * FileStream_CreateFile(const char * szFileName);
TFileStream * FileStream_OpenFile(const char * szFileName, bool bWriteAccess);
TFileStream * FileStream_OpenEncrypted(const char * szFileName);
bool FileStream_GetPos(TFileStream * pStream, ULONGLONG & ByteOffset);
bool FileStream_Read(TFileStream * pStream, ULONGLONG * pByteOffset, void * pvBuffer, DWORD dwBytesToRead);
bool FileStream_Write(TFileStream * pStream, ULONGLONG * pByteOffset, const void * pvBuffer, DWORD dwBytesToWrite);
bool FileStream_GetLastWriteTime(TFileStream * pStream, ULONGLONG * pFT);
bool FileStream_GetSize(TFileStream * pStream, ULONGLONG & FileSize);
bool FileStream_SetSize(TFileStream * pStream, ULONGLONG NewFileSize);
bool FileStream_MoveFile(TFileStream * pStream, TFileStream * pTempStream);
void FileStream_Close(TFileStream * pStream);

//-----------------------------------------------------------------------------
// Functions prototypes for Storm.dll

// Typedefs for functions exported by Storm.dll
typedef LCID  (WINAPI * SFILESETLOCALE)(LCID);
typedef bool  (WINAPI * SFILEOPENARCHIVE)(const char *, DWORD, DWORD, HANDLE *);
typedef bool  (WINAPI * SFILECLOSEARCHIVE)(HANDLE);
typedef bool  (WINAPI * SFILEOPENFILEEX)(HANDLE, const char *, DWORD, HANDLE *);
typedef bool  (WINAPI * SFILECLOSEFILE)(HANDLE);
typedef DWORD (WINAPI * SFILEGETFILESIZE)(HANDLE, LPDWORD);
typedef DWORD (WINAPI * SFILESETFILEPOINTER)(HANDLE, LONG, LONG *, DWORD);
typedef bool  (WINAPI * SFILEREADFILE)(HANDLE, void *, DWORD, LPDWORD, LPOVERLAPPED);

//-----------------------------------------------------------------------------
// Functions for archive manipulation

bool   WINAPI SFileOpenArchive(const char * szMpqName, DWORD dwPriority, DWORD dwFlags, HANDLE * phMpq);
bool   WINAPI SFileCreateArchive(const char * szMpqName, DWORD dwFlags, DWORD dwHashTableSize, HANDLE * phMpq);

LCID   WINAPI SFileSetLocale(LCID lcNewLocale);
LCID   WINAPI SFileGetLocale();
bool   WINAPI SFileFlushArchive(HANDLE hMpq);
bool   WINAPI SFileCloseArchive(HANDLE hMpq);

// Adds another listfile into MPQ. The currently added listfile(s) remain,
// so you can use this API to combining more listfiles.
// Note that this function is internally called by SFileFindFirstFile
int    WINAPI SFileAddListFile(HANDLE hMpq, const char * szListFile);

// Archive compacting
bool   WINAPI SFileSetCompactCallback(HANDLE hMpq, SFILE_COMPACT_CALLBACK CompactCB, void * pvData);
bool   WINAPI SFileCompactArchive(HANDLE hMpq, const char * szListFile = NULL, bool bReserved = 0);

// Changing hash table size
bool   WINAPI SFileSetHashTableSize(HANDLE hMpq, DWORD dwHashTableSize);

// Changing (attributes) file
DWORD  WINAPI SFileGetAttributes(HANDLE hMpq);
bool   WINAPI SFileSetAttributes(HANDLE hMpq, DWORD dwFlags);
bool   WINAPI SFileUpdateFileAttributes(HANDLE hMpq, const char * szFileName);

//-----------------------------------------------------------------------------
// Functions for manipulation with patch archives

bool   WINAPI SFileOpenPatchArchive(HANDLE hMpq, const char * szPatchMpqName, const char * szPatchPathPrefix, DWORD dwFlags);
bool   WINAPI SFileIsPatchedArchive(HANDLE hMpq);

//-----------------------------------------------------------------------------
// Functions for file manipulation

// Reading from MPQ file
bool   WINAPI SFileOpenFileEx(HANDLE hMpq, const char * szFileName, DWORD dwSearchScope, HANDLE * phFile);
DWORD  WINAPI SFileGetFileSize(HANDLE hFile, LPDWORD pdwFileSizeHigh = NULL);
DWORD  WINAPI SFileSetFilePointer(HANDLE hFile, LONG lFilePos, LONG * plFilePosHigh, DWORD dwMoveMethod);
bool   WINAPI SFileReadFile(HANDLE hFile, void * lpBuffer, DWORD dwToRead, LPDWORD pdwRead = NULL, LPOVERLAPPED lpOverlapped = NULL);
bool   WINAPI SFileCloseFile(HANDLE hFile);

// Retrieving info about the file
bool   WINAPI SFileHasFile(HANDLE hMpq, const char * szFileName);
bool   WINAPI SFileGetFileName(HANDLE hFile, char * szFileName);
bool   WINAPI SFileGetFileInfo(HANDLE hMpqOrFile, DWORD dwInfoType, void * pvFileInfo, DWORD cbFileInfo, LPDWORD pcbLengthNeeded = NULL);

// High-level extract function
bool   WINAPI SFileExtractFile(HANDLE hMpq, const char * szToExtract, const char * szExtracted);

//-----------------------------------------------------------------------------
// Functions for file and archive verification

// Verifies file against its checksums stored in (attributes) attributes (depending on dwFlags).
// For dwFlags, use one or more of MPQ_ATTRIBUTE_MD5
DWORD  WINAPI SFileVerifyFile(HANDLE hMpq, const char * szFileName, DWORD dwFlags);

// Verifies raw data of the archive. Only works for MPQs version 4.0 or newer
int    WINAPI SFileVerifyRawData(HANDLE hMpq, DWORD dwWhatToVerify, const char * szFileName);

// Verifies the signature, if present
DWORD  WINAPI SFileVerifyArchive(HANDLE hMpq);

//-----------------------------------------------------------------------------
// Functions for file searching

HANDLE WINAPI SFileFindFirstFile(HANDLE hMpq, const char * szMask, SFILE_FIND_DATA * lpFindFileData, const char * szListFile);
bool   WINAPI SFileFindNextFile(HANDLE hFind, SFILE_FIND_DATA * lpFindFileData);
bool   WINAPI SFileFindClose(HANDLE hFind);

HANDLE WINAPI SListFileFindFirstFile(HANDLE hMpq, const char * szListFile, const char * szMask, SFILE_FIND_DATA * lpFindFileData);
bool   WINAPI SListFileFindNextFile(HANDLE hFind, SFILE_FIND_DATA * lpFindFileData);
bool   WINAPI SListFileFindClose(HANDLE hFind);

// Locale support
int    WINAPI SFileEnumLocales(HANDLE hMpq, const char * szFileName, LCID * plcLocales, LPDWORD pdwMaxLocales, DWORD dwSearchScope);

//-----------------------------------------------------------------------------
// Support for adding files to the MPQ

bool   WINAPI SFileCreateFile(HANDLE hMpq, const char * szArchivedName, ULONGLONG FileTime, DWORD dwFileSize, LCID lcLocale, DWORD dwFlags, HANDLE * phFile);
bool   WINAPI SFileWriteFile(HANDLE hFile, const void * pvData, DWORD dwSize, DWORD dwCompression);
bool   WINAPI SFileFinishFile(HANDLE hFile);
bool   WINAPI SFileAddFileEx(HANDLE hMpq, const char * szFileName, const char * szArchivedName, DWORD dwFlags, DWORD dwCompression, DWORD dwCompressionNext = 0xFFFFFFFF);
bool   WINAPI SFileAddFile(HANDLE hMpq, const char * szFileName, const char * szArchivedName, DWORD dwFlags);
bool   WINAPI SFileAddWave(HANDLE hMpq, const char * szFileName, const char * szArchivedName, DWORD dwFlags, DWORD dwQuality);
bool   WINAPI SFileRemoveFile(HANDLE hMpq, const char * szFileName, DWORD dwSearchScope);
bool   WINAPI SFileRenameFile(HANDLE hMpq, const char * szOldFileName, const char * szNewFileName);
bool   WINAPI SFileSetFileLocale(HANDLE hFile, LCID lcNewLocale);
bool   WINAPI SFileSetDataCompression(DWORD DataCompression);

bool   WINAPI SFileSetAddFileCallback(HANDLE hMpq, SFILE_ADDFILE_CALLBACK AddFileCB, void * pvData);

//-----------------------------------------------------------------------------
// Compression and decompression

int    WINAPI SCompImplode    (char * pbOutBuffer, int * pcbOutBuffer, char * pbInBuffer, int cbInBuffer);
int    WINAPI SCompExplode    (char * pbOutBuffer, int * pcbOutBuffer, char * pbInBuffer, int cbInBuffer);
int    WINAPI SCompCompress   (char * pbOutBuffer, int * pcbOutBuffer, char * pbInBuffer, int cbInBuffer, unsigned uCompressionMask, int nCmpType, int nCmpLevel);
int    WINAPI SCompDecompress (char * pbOutBuffer, int * pcbOutBuffer, char * pbInBuffer, int cbInBuffer);

//-----------------------------------------------------------------------------
// Functions from Storm.dll. They use slightly different names for keeping
// possibility to use them together with StormLib (StormXXX instead of SFileXXX)

#ifdef __LINK_STORM_DLL__
  #define STORM_ALTERNATE_NAMES         // Force storm_dll.h to use alternate fnc names
  #include "..\storm_dll\storm_dll.h"
#endif // __LINK_STORM_DLL__

#endif  // __STORMLIB_H_