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

#ifndef TYPEDEFS_H
#define TYPEDEFS_H

#ifdef _WIN32
    typedef __int64            int64;
    typedef __int32            int32;
    typedef __int16            int16;
    typedef __int8             int8;
    typedef unsigned __int64   uint64;
    typedef unsigned __int32   uint32;
    typedef unsigned __int16   uint16;
    typedef unsigned __int8    uint8;
#else
    #include <stdint.h>
    #ifndef uint64_t
        #ifdef __linux__
            #include <linux/types.h>
        #endif
    #endif
    typedef int64_t            int64;
    typedef int32_t            int32;
    typedef int16_t            int16;
    typedef int8_t             int8;
    typedef uint64_t           uint64;
    typedef uint32_t           uint32;
    typedef uint16_t           uint16;
    typedef uint8_t            uint8;
#endif

#endif