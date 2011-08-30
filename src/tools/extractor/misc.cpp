/*
 * Copyright (C) 2010-2011 CactusEMU <http://www.cactusemu.com/>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#include "headers.h"
#include "misc.h"
#include "MPQ.h"

bool FileExists( const char* FileName )
{
    FILE *fp = fopen(FileName,"r");
    if ( fp )
    {
        fclose(fp);
        return true;
    }
    return false;
}

void CreateDir( const std::string& Path )
{
#ifdef _WIN32
    _mkdir(Path.c_str());
#else
    mkdir(Path.c_str(), 0777);
#endif
}

int ReadBuild(int locale)
{
    // include build info file also
    std::string filename  = std::string("component.wow-")+langs[locale]+".txt";
    //printf("Read %s file... ", filename.c_str());

    CreateDir("./dbc/");
    ExtractFileToHardDrive(localeMPQ[0], filename.c_str(), (std::string("./dbc/") + filename).c_str());

    std::string text;
    std::string temp;

    std::ifstream fichier((std::string("./dbc/") + filename).c_str(), std::ios::in);
    if (!fichier)
        assert(false && "Error when loading component.wow-...");
    while(fichier)
    {
        fichier >> temp;
        text += temp;
    }

    size_t pos = text.find("version=\"");
    size_t pos1 = pos + strlen("version=\"");
    size_t pos2 = text.find("\"",pos1);
    if (pos == text.npos || pos2 == text.npos || pos1 >= pos2)
    {
        printf("Fatal error: Invalid  %s file format!\n", filename.c_str());
        exit(1);
    }

    std::string build_str = text.substr(pos1,pos2-pos1);

    int build = atoi(build_str.c_str());
    if (build <= 0)
    {
        printf("Fatal error: Invalid  %s file format!\n", filename.c_str());
        exit(1);
    }

    return build;
}