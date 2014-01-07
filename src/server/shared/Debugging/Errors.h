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

#ifndef SKYFIRE_ERRORS_H
#define SKYFIRE_ERRORS_H

#include "Define.h"

namespace SkyFire
{

    DECLSPEC_NORETURN void Assert(char const* file, int line, char const* function, char const* message) ATTR_NORETURN;

    DECLSPEC_NORETURN void Fatal(char const* file, int line, char const* function, char const* message) ATTR_NORETURN;

    DECLSPEC_NORETURN void Error(char const* file, int line, char const* function, char const* message) ATTR_NORETURN;

    void Warning(char const* file, int line, char const* function, char const* message);

} // namespace SkyFire

#define WPAssert(cond) do { if (!(cond)) SkyFire::Assert(__FILE__, __LINE__, __FUNCTION__, #cond); } while (0)
#define WPFatal(cond, msg) do { if (!(cond)) SkyFire::Fatal(__FILE__, __LINE__, __FUNCTION__, (msg)); } while (0)
#define WPError(cond, msg) do { if (!(cond)) SkyFire::Error(__FILE__, __LINE__, __FUNCTION__, (msg)); } while (0)
#define WPWarning(cond, msg) do { if (!(cond)) SkyFire::Warning(__FILE__, __LINE__, __FUNCTION__, (msg)); } while (0)

#define ASSERT WPAssert

#endif
