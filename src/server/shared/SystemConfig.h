/*
 * Copyright (C) 2011-2014 Project SkyFire <http://www.projectskyfire.org/>
 * Copyright (C) 2008-2014 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2005-2014 MaNGOS <http://getmangos.com/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 3 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef SKYFIRE_SYSTEMCONFIG_H
#define SKYFIRE_SYSTEMCONFIG_H

#include "Define.h"
#include "revision.h"

#define _PACKAGENAME "SkyFireEMU"

#if SKYFIRE_ENDIAN == SKYFIRE_BIGENDIAN
# define _ENDIAN_STRING "big-endian"
#else
# define _ENDIAN_STRING "little-endian"
#endif

#define _CLIENT_BUILD_REVISION "4.0.6a - 13623"

#define _CLIENT_BUILD_REVISION_2 "4.0.6a - 13623 (c)ProjectSkyFire <http://www.projectskyfire.org>"  // DO NOT REMOVE OR ALTER OUR COPYRIGHTS!

#if PLATFORM == PLATFORM_WINDOWS
# ifdef _WIN64
#  define _FULLVERSION _PACKAGENAME " rev. " VER_PRODUCTVERSION_STR " (Win64, " _BUILD_DIRECTIVE ")"
# else
#  define _FULLVERSION _PACKAGENAME " rev. " VER_PRODUCTVERSION_STR " (Win32, " _BUILD_DIRECTIVE ")"
# endif
#else
#  define _FULLVERSION _PACKAGENAME " rev. " VER_PRODUCTVERSION_STR " (Unix, " _BUILD_DIRECTIVE ")"
#endif
#endif
