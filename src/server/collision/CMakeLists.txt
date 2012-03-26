# Copyright (C) 2011-2012 Project SkyFire <http://www.projectskyfire.org/>
# Copyright (C) 2008-2012 TrinityCore <http://www.trinitycore.org/>
#
# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without
# modifications, as long as this notice is preserved.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

if( USE_COREPCH )
  include_directories(${CMAKE_CURRENT_BINARY_DIR})
endif()

file(GLOB_RECURSE sources_Management Management/*.cpp Management/*.h)
file(GLOB_RECURSE sources_Maps Maps/*.cpp Maps/*.h)
file(GLOB_RECURSE sources_Models Models/*.cpp Models/*.h)
file(GLOB_RECURSE sources_Pathfinding Pathfinding/*.cpp Pathfinding/*.h)

file(GLOB sources_localdir *.cpp *.h)

#
# Build collision sourcelist
#

if( USE_COREPCH AND MSVC )
  set(collision_STAT_SRCS
    PrecompiledHeaders/collisionPCH.cpp
    PrecompiledHeaders/collisionPCH.h
  )
endif()

set(collision_STAT_SRCS
  ${collision_STAT_SRCS}
  ${sources_Management}
  ${sources_Maps}
  ${sources_Models}
  ${sources_Pathfinding}
  ${sources_localdir}
)

include_directories(
  ${CMAKE_SOURCE_DIR}/dep/g3dlite/include
  ${CMAKE_SOURCE_DIR}/dep/recastlite/Detour
  ${CMAKE_SOURCE_DIR}/dep/recastlite/Recast
  ${CMAKE_SOURCE_DIR}/src/Server/Shared
  ${CMAKE_SOURCE_DIR}/src/server/Shared/Configuration
  ${CMAKE_SOURCE_DIR}/src/Server/Shared/Debugging
  ${CMAKE_SOURCE_DIR}/src/Server/Shared/Database
  ${CMAKE_SOURCE_DIR}/src/Server/Shared/Debugging
  ${CMAKE_SOURCE_DIR}/src/Server/Shared/Dynamic
  ${CMAKE_SOURCE_DIR}/src/Server/Shared/Dynamic/LinkedReference
  ${CMAKE_SOURCE_DIR}/src/Server/Shared/Logging
  ${CMAKE_SOURCE_DIR}/src/Server/Shared/Threading
  ${CMAKE_SOURCE_DIR}/src/Server/Shared/Packets
  ${CMAKE_SOURCE_DIR}/src/Server/Shared/Utilities
  ${CMAKE_SOURCE_DIR}/src/Server/Game
  ${CMAKE_SOURCE_DIR}/src/Server/Game/Entities
  ${CMAKE_SOURCE_DIR}/src/Server/Game/Addons
  ${CMAKE_SOURCE_DIR}/src/Server/Game/World
  ${CMAKE_SOURCE_DIR}/src/Server/Game/Entities/Creature
  ${CMAKE_SOURCE_DIR}/src/Server/Game/Entities/Unit
  ${CMAKE_SOURCE_DIR}/src/Server/Game/Entities/Object
  ${CMAKE_SOURCE_DIR}/src/Server/Game/Entities/Object/Updates
  ${CMAKE_SOURCE_DIR}/src/Server/Game/Entities/Vehicle
  ${CMAKE_SOURCE_DIR}/src/Server/Game/Entities/Item
  ${CMAKE_SOURCE_DIR}/src/Server/Game/Grids
  ${CMAKE_SOURCE_DIR}/src/Server/Game/Grids/Cells
  ${CMAKE_SOURCE_DIR}/src/Server/Game/Miscellaneous
  ${CMAKE_SOURCE_DIR}/src/Server/Game/Maps
  ${CMAKE_SOURCE_DIR}/src/Server/Game/DataStores
  ${CMAKE_SOURCE_DIR}/src/Server/Game/Movement
  ${CMAKE_SOURCE_DIR}/src/Server/Game/Movement/Waypoints
  ${CMAKE_SOURCE_DIR}/src/Server/Game/Server
  ${CMAKE_SOURCE_DIR}/src/Server/Game/Server/Protocol
  ${CMAKE_SOURCE_DIR}/src/Server/Game/Spells
  ${CMAKE_SOURCE_DIR}/src/Server/Game/Spells/Auras
  ${CMAKE_SOURCE_DIR}/src/Server/Game/Combat
  ${CMAKE_SOURCE_DIR}/src/Server/Game/Loot
  ${CMAKE_SOURCE_DIR}/src/Server/Game/Conditions
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/Management
  ${CMAKE_CURRENT_SOURCE_DIR}/Maps
  ${CMAKE_CURRENT_SOURCE_DIR}/Models
  ${CMAKE_BINARY_DIR}
  ${ACE_INCLUDE_DIR}
  ${MYSQL_INCLUDE_DIR}
  ${OPENSSL_INCLUDE_DIR}
)

add_library(collision STATIC ${collision_STAT_SRCS})

# Generate precompiled header
if( USE_COREPCH )
  if(CMAKE_COMPILER_IS_GNUCXX)
    add_precompiled_header(collision ${CMAKE_CURRENT_SOURCE_DIR}/PrecompiledHeaders/collisionPCH.h)
  elseif(MSVC)
    add_native_precompiled_header(collision ${CMAKE_CURRENT_SOURCE_DIR}/PrecompiledHeaders/collisionPCH)
  endif()
endif()

