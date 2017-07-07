# Copyright (C) 2011-2017 Project SkyFire <http://www.projectskyfire.org/>
# Copyright (C) 2008-2017 TrinityCore <http://www.trinitycore.org/>
#
# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without
# modifications, as long as this notice is preserved.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.


# Package overloads
set(ACE_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/dep/acelite)
set(ACE_LIBRARY "ace")
set(BZIP2_LIBRARIES "bzip2")
set(ZLIB_LIBRARIES "zlib")

# We require at least Visual Studio 2017 (aka 14.0) which has version nr 1900.
IF(NOT FORCE_UNSUPPORTED_COMPILER AND MSVC_VERSION LESS 1900)
  MESSAGE(FATAL_ERROR "Visual Studio 2017 or newer is required!")
ENDIF()

# check the CMake preload parameters (commented out by default)

# overload CMAKE_INSTALL_PREFIX if not being set properly
#if( WIN32 )
#  if( NOT CYGWIN )
#    if( NOT CMAKE_INSTALL_PREFIX )
#      set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/bin")
#    endif()
#  endif()
#endif()

if( MSVC )
    include(${CMAKE_SOURCE_DIR}/cmake/compiler/msvc/settings.cmake)
endif()

if( MSYS OR MINGW )
    include(${CMAKE_SOURCE_DIR}/cmake/compiler/gcc/settings.cmake)
endif()