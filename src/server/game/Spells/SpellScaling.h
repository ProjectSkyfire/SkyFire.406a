/*
 * Copyright (C) 2010-2011 Project SkyFire <http://www.projectskyfire.org/>
 * Copyright (C) 2008-2011 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2005-2009 MaNGOS <http://getmangos.com/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
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

#ifndef _SPELLSCALING_H
#define _SPELLSCALING_H

#include "SharedDefines.h"
#include "DBCStores.h"

class SpellInfo;

class SpellScaling
{
    bool  _canScale;
    int32 _castTime;

public:
    float avg[3];
    float min[3];
    float max[3];
    float pts[3];

    bool  CanUseScale() { return _canScale; }
    int32 GetCastTime() { return _castTime; }

    float GetGtSpellScalingValue(int8 classId, uint8 level)
    {
        classId = classId < 0 ? MAX_CLASSES : classId;

        float _coef = -1.0f;
        if (classId)
        {
            GtSpellScalingEntry const* spellscaling = sGtSpellScalingStore.LookupEntry((classId - 1) * 100 + level);
            _coef = spellscaling ? spellscaling->coef : _coef;
        }

        return _coef;
    }

    SpellScaling(SpellInfo const* spellInfo, uint8 level)
    {
        _canScale = false;
        _castTime = 0;

        for (uint8 i = 0; i < 3; i++)
        {
            avg[i] = 0.0f;
            min[i] = 0.0f;
            max[i] = 0.0f;
            pts[i] = 0.0f;
        }

        if (!spellInfo || !spellInfo->SpellScalingId)
            return;

        if (!spellInfo->playerClass)
            return;

        float CoefBase = spellInfo->CoefBase;
        uint8 CoefBaseLevel = spellInfo->CoefLevelBase;
        int32 castTimeMin = spellInfo->castTimeMin;
        int32 castTimeMax = spellInfo->castTimeMax;
        uint8 castScalingMaxLevel = spellInfo->castScalingMaxLevel;

        float gtCoef = GetGtSpellScalingValue(spellInfo->playerClass, level);
        if (gtCoef == -1.0f)
            return;

        gtCoef *= (std::min(level, CoefBaseLevel) + (CoefBase * std::max(0, level - CoefBaseLevel))) / level;

        // Cast time
        if (castTimeMax > 0 && level > 1)
            _castTime = castTimeMin + (((level - 1) * (castTimeMax - castTimeMin)) / (castScalingMaxLevel - 1));
        else
            _castTime = castTimeMin;

        _castTime = _castTime > castTimeMax ? castTimeMax : _castTime;

        // Effects
        for (uint8 effIndex = 0; effIndex < 3; effIndex++)
        {
            float mult = spellInfo->Multiplier[effIndex];
            float randommult = spellInfo->RandomMultiplier[effIndex];
            float othermult = spellInfo->OtherMultiplier[effIndex];

            avg[effIndex] = mult * gtCoef;
            if (castTimeMax > 0)
                avg[effIndex] *= float(_castTime)/float(castTimeMax);

            min[effIndex] = roundf(avg[effIndex]) - std::floor(avg[effIndex] * randommult / 2);
            max[effIndex] = roundf(avg[effIndex]) + std::floor(avg[effIndex] * randommult / 2);
            pts[effIndex] = roundf(othermult * gtCoef);
            avg[effIndex] = std::max((float)ceil(mult), roundf(avg[effIndex]));
        }

        _canScale = true;
    }
};

#endif // _SPELLSCALING_H
