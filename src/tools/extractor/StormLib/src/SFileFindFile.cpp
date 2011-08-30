/*****************************************************************************/
/* SFileFindFile.cpp                      Copyright (c) Ladislav Zezula 2003 */
/*---------------------------------------------------------------------------*/
/* A module for file searching within MPQs                                   */
/*---------------------------------------------------------------------------*/
/*   Date    Ver   Who  Comment                                              */
/* --------  ----  ---  -------                                              */
/* 25.03.03  1.00  Lad  The first version of SFileFindFile.cpp               */
/*****************************************************************************/

#define __STORMLIB_SELF__
#include "StormLib.h"
#include "StormCommon.h"

//-----------------------------------------------------------------------------
// Defines

#define LISTFILE_CACHE_SIZE 0x1000

//-----------------------------------------------------------------------------
// Private structure used for file search (search handle)

// Used by searching in MPQ archives
struct TMPQSearch
{
    TMPQArchive * ha;                   // Handle to MPQ, where the search runs
    DWORD  dwNextIndex;                 // Next file index to be checked
    DWORD  dwName1;                     // Lastly found Name1
    DWORD  dwName2;                     // Lastly found Name2
    char   szSearchMask[1];             // Search mask (variable length)
};

//-----------------------------------------------------------------------------
// Local functions

static bool IsValidSearchHandle(TMPQSearch * hs)
{
    if (hs == NULL)
        return false;

    return IsValidMpqHandle(hs->ha);
}

bool CheckWildCard(const char * szString, const char * szWildCard)
{
    const char * szSubString;
    int nSubStringLength;
    int nMatchCount = 0;

    // When the mask is empty, it never matches
    if (szWildCard == NULL || *szWildCard == 0)
        return false;

    // If the wildcard contains just "*", then it always matches
    if (szWildCard[0] == '*' && szWildCard[1] == 0)
        return true;

    // Do normal test
    for(;;)
    {
        // If there is '?' in the wildcard, we skip one char
        while(*szWildCard == '?')
        {
            szWildCard++;
            szString++;
        }

        // If there is '*', means zero or more chars. We have to
        // find the sequence after '*'
        if (*szWildCard == '*')
        {
            // More stars is equal to one star
            while(*szWildCard == '*' || *szWildCard == '?')
                szWildCard++;

            // If we found end of the wildcard, it's a match
            if (*szWildCard == 0)
                return true;

            // Determine the length of the substring in szWildCard
            szSubString = szWildCard;
            while(*szSubString != 0 && *szSubString != '?' && *szSubString != '*')
                szSubString++;
            nSubStringLength = (int)(szSubString - szWildCard);
            nMatchCount = 0;

            // Now we have to find a substring in szString,
            // that matches the substring in szWildCard
            while(*szString != 0)
            {
                // Calculate match count
                while(nMatchCount < nSubStringLength)
                {
                    if (toupper(szString[nMatchCount]) != toupper(szWildCard[nMatchCount]))
                        break;
                    if (szString[nMatchCount] == 0)
                        break;
                    nMatchCount++;
                }

                // If the match count has reached substring length, we found a match
                if (nMatchCount == nSubStringLength)
                {
                    szWildCard += nMatchCount;
                    szString += nMatchCount;
                    break;
                }

                // No match, move to the next char in szString
                nMatchCount = 0;
                szString++;
            }
        }
        else
        {
            // If we came to the end of the string, compare it to the wildcard
            if (toupper(*szString) != toupper(*szWildCard))
                return false;

            // If we arrived to the end of the string, it's a match
            if (*szString == 0)
                return true;

            // Otherwise, continue in comparing
            szWildCard++;
            szString++;
        }
    }
}

// Performs one MPQ search
static int DoMPQSearch(TMPQSearch * hs, SFILE_FIND_DATA * lpFindFileData)
{
    TMPQArchive * ha = hs->ha;
    TFileEntry * pFileTableEnd;
    TFileEntry * pFileEntry;
    const char * szFileName;
    char szPseudoName[20];
    DWORD dwBlockIndex;
    size_t nPrefixLength;

    // Do that for all files in the patch chain
    while(ha != NULL)
    {
        // Now parse the file entry table in order to get all files.
        pFileTableEnd = ha->pFileTable + ha->dwFileTableSize;
        pFileEntry = ha->pFileTable + hs->dwNextIndex;

        // Get the start and end of the hash table
        nPrefixLength = strlen(ha->szPatchPrefix);

        // Parse the file table
        while(pFileEntry < pFileTableEnd)
        {
            // Increment the next index for subsequent search
            hs->dwNextIndex++;

            // Does the block exist ?
            if (pFileEntry->dwFlags & MPQ_FILE_EXISTS)
            {
                // Prepare the block index
                dwBlockIndex = (DWORD)(pFileEntry - ha->pFileTable);

                // Get the file name. If it's not known, we will create pseudo-name
                szFileName = pFileEntry->szFileName;
                if (szFileName == NULL)
                {
                    HANDLE hFile;

                    // Open the file by index in order to force getting file name
                    if (SFileOpenFileEx((HANDLE)hs->ha, (char *)(DWORD_PTR)dwBlockIndex, SFILE_OPEN_BY_INDEX, &hFile))
                        SFileCloseFile(hFile);

                    // If the name was retrieved, use that one. Otherwise, just use generic pseudo-name
                    szFileName = pFileEntry->szFileName;
                    if (szFileName == NULL)
                    {
                        sprintf(szPseudoName, "File%08u.xxx", dwBlockIndex);
                        szFileName = szPseudoName;
                    }
                }

                // If we are already in the patch MPQ, we skip all files
                // that don't have the appropriate patch prefix and are patch files
                if (nPrefixLength)
                {
                    // We want to return patch files, because the calling
                    // application might want to update size
//                  if (pFileEntry->dwFlags & MPQ_FILE_PATCH_FILE)
//                      goto __SkipThisFile;
                    if (_strnicmp(szFileName, ha->szPatchPrefix, nPrefixLength))
                        goto __SkipThisFile;
                }

                // Check the file name.
                if (CheckWildCard(szFileName, hs->szSearchMask))
                {
                    // Fill the found entry
                    lpFindFileData->dwHashIndex  = pFileEntry->dwHashIndex;
                    lpFindFileData->dwBlockIndex = dwBlockIndex;
                    lpFindFileData->dwFileSize   = pFileEntry->dwFileSize;
                    lpFindFileData->dwFileFlags  = pFileEntry->dwFlags;
                    lpFindFileData->dwCompSize   = pFileEntry->dwCmpSize;
                    lpFindFileData->lcLocale     = pFileEntry->lcLocale;

                    // Fill the filetime
                    lpFindFileData->dwFileTimeHi = (DWORD)(pFileEntry->FileTime >> 32);
                    lpFindFileData->dwFileTimeLo = (DWORD)(pFileEntry->FileTime);

                    // Fill the file name and plain file name
                    strcpy(lpFindFileData->cFileName, szFileName + nPrefixLength);
                    lpFindFileData->szPlainName = (char *)GetPlainFileName(lpFindFileData->cFileName);
                    return ERROR_SUCCESS;
                }
            }

            // Move to the next file entry
            __SkipThisFile:

            pFileEntry++;
        }

        // Move to the next patch in the patch chain
        hs->ha = ha = ha->haPatch;
        hs->dwNextIndex = 0;
    }

    // No more files found, return error
    return ERROR_NO_MORE_FILES;
}

static void FreeMPQSearch(TMPQSearch *& hs)
{
    if (hs != NULL)
    {
        FREEMEM(hs);
        hs = NULL;
    }
}

//-----------------------------------------------------------------------------
// Public functions

HANDLE WINAPI SFileFindFirstFile(HANDLE hMpq, const char * szMask, SFILE_FIND_DATA * lpFindFileData, const char * szListFile)
{
    TMPQArchive * ha = (TMPQArchive *)hMpq;
    TMPQSearch * hs = NULL;             // Search object handle
    size_t nSize  = 0;
    int nError = ERROR_SUCCESS;

    // Check for the valid parameters
    if (!IsValidMpqHandle(ha))
        nError = ERROR_INVALID_HANDLE;
    if (szMask == NULL || lpFindFileData == NULL)
        nError = ERROR_INVALID_PARAMETER;

    // Include the listfile into the MPQ's internal listfile
    // Note that if the listfile name is NULL, do nothing because the
    // internal listfile is always included.
    if (nError == ERROR_SUCCESS && szListFile != NULL && *szListFile != 0)
        nError = SFileAddListFile((HANDLE)ha, szListFile);

    // Allocate the structure for MPQ search
    if (nError == ERROR_SUCCESS)
    {
        nSize = sizeof(TMPQSearch) + strlen(szMask) + 1;
        if ((hs = (TMPQSearch *)ALLOCMEM(char, nSize)) == NULL)
            nError = ERROR_NOT_ENOUGH_MEMORY;
    }

    // Perform the first search
    if (nError == ERROR_SUCCESS)
    {
        memset(hs, 0, sizeof(TMPQSearch));
        strcpy(hs->szSearchMask, szMask);
        hs->ha = ha;
        nError = DoMPQSearch(hs, lpFindFileData);
    }

    // Cleanup
    if (nError != ERROR_SUCCESS)
    {
        FreeMPQSearch(hs);
        SetLastError(nError);
    }

    // Return the result value
    return (HANDLE)hs;
}

bool WINAPI SFileFindNextFile(HANDLE hFind, SFILE_FIND_DATA * lpFindFileData)
{
    TMPQSearch * hs = (TMPQSearch *)hFind;
    int nError = ERROR_SUCCESS;

    // Check the parameters
    if (!IsValidSearchHandle(hs))
        nError = ERROR_INVALID_HANDLE;
    if (lpFindFileData == NULL)
        nError = ERROR_INVALID_PARAMETER;

    if (nError == ERROR_SUCCESS)
        nError = DoMPQSearch(hs, lpFindFileData);

    if (nError != ERROR_SUCCESS)
        SetLastError(nError);
    return (nError == ERROR_SUCCESS);
}

bool WINAPI SFileFindClose(HANDLE hFind)
{
    TMPQSearch * hs = (TMPQSearch *)hFind;

    // Check the parameters
    if (!IsValidSearchHandle(hs))
    {
        SetLastError(ERROR_INVALID_HANDLE);
        return false;
    }

    FreeMPQSearch(hs);
    return true;
}