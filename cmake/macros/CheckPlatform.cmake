# Copyright (C) 2011-2014 Project SkyFire <http://www.projectskyfire.org/>
# Copyright (C) 2008-2014 TrinityCore <http://www.trinitycore.org/>
#
# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without
# modifications, as long as this notice is preserved.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

# check what platform we're on (64-bit or 32-bit), and create a simpler test than CMAKE_SIZEOF_VOID_P
if(CMAKE_SIZEOF_VOID_P MATCHES 8)
    set(PLATFORM 64)
    MESSAGE(STATUS "Detected 64-bit platform")
else()
    set(PLATFORM 32)
    MESSAGE(STATUS "Detected 32-bit platform")
endif()

include("${CMAKE_SOURCE_DIR}/cmake/platform/settings.cmake")

if(WIN32)
  include("${CMAKE_SOURCE_DIR}/cmake/platform/win/settings.cmake")
elseif(APPLE)
  include("${CMAKE_SOURCE_DIR}/cmake/platform/osx/settings.cmake")
elseif(UNIX)
  include("${CMAKE_SOURCE_DIR}/cmake/platform/unix/settings.cmake")
endif()
