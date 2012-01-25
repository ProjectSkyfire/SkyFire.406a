/*
 * Copyright (C) 2005-2011 MaNGOS <http://getmangos.com/>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "MovementPacketBuilder.h"
#include "MoveSpline.h"
#include "WorldPacket.h"
#include "Unit.h"

namespace Movement
{
    inline void operator << (ByteBuffer& b, const Vector3& v)
    {
        b << v.x << v.y << v.z;
    }

    inline void operator >> (ByteBuffer& b, Vector3& v)
    {
        b >> v.x >> v.y >> v.z;
    }

    enum MonsterMoveType
    {
        MonsterMoveNormal       = 0,
        MonsterMoveStop         = 1,
        MonsterMoveFacingSpot   = 2,
        MonsterMoveFacingTarget = 3,
        MonsterMoveFacingAngle  = 4
    };

    void PacketBuilder::WriteCommonMonsterMovePart(const MoveSpline& move_spline, WorldPacket& data)
    {
        MoveSplineFlag splineflags = move_spline.splineflags;

        data << uint8(0);
        data << move_spline.spline.getPoint(move_spline.spline.first());
        data << move_spline.GetId();

        switch(splineflags & MoveSplineFlag::Mask_Final_Facing)
        {
        default:
            data << uint8(MonsterMoveNormal);
            break;
        case MoveSplineFlag::Final_Target:
            data << uint8(MonsterMoveFacingTarget);
            data << move_spline.facing.target;
            break;
        case MoveSplineFlag::Final_Angle:
            data << uint8(MonsterMoveFacingAngle);
            data << move_spline.facing.angle;
            break;
        case MoveSplineFlag::Final_Point:
            data << uint8(MonsterMoveFacingSpot);
            data << move_spline.facing.f.x << move_spline.facing.f.y << move_spline.facing.f.z;
            break;
        }

        // add fake Enter_Cycle flag - needed for client-side cyclic movement (client will erase first spline vertex after first cycle done)
        splineflags.enter_cycle = move_spline.isCyclic();
        data << uint32(splineflags & ~MoveSplineFlag::Mask_No_Monster_Move);

        if (splineflags.animation && splineflags.animation2)
        {
            data << splineflags.getAnimationId();
            data << move_spline.effect_start_time;
        }

        data << move_spline.Duration();

        if (splineflags.parabolic)
        {
            data << move_spline.vertical_acceleration;
            data << move_spline.effect_start_time;
        }
    }

    void WriteLinearPath(const Spline<int32>& spline, ByteBuffer& data)
    {
        uint32 last_idx = spline.getPointCount() - 3;
        const Vector3 * real_path = &spline.getPoint(1);

        data << last_idx;
        data << real_path[last_idx];   // destination
        if (last_idx > 1)
        {
            Vector3 middle = (real_path[0] + real_path[last_idx]) / 2.f;
            Vector3 offset;
            // first and last points already appended
            for(uint32 i = 1; i < last_idx; ++i)
            {
                offset = middle - real_path[i];
                data.appendPackXYZ(offset.x, offset.y, offset.z);
            }
        }
    }

    void WriteCatmullRomPath(const Spline<int32>& spline, ByteBuffer& data)
    {
        uint32 count = spline.getPointCount() - 3;
        data << count;
        data.append<Vector3>(&spline.getPoint(2), count);
    }

    void WriteCatmullRomCyclicPath(const Spline<int32>& spline, ByteBuffer& data)
    {
        uint32 count = spline.getPointCount() - 3;
        data << uint32(count + 1);
        data << spline.getPoint(1); // fake point, client will erase it from the spline after first cycle done
        data.append<Vector3>(&spline.getPoint(1), count);
    }

    void PacketBuilder::WriteMonsterMove(const MoveSpline& move_spline, WorldPacket& data)
    {
        WriteCommonMonsterMovePart(move_spline, data);

        const Spline<int32>& spline = move_spline.spline;
        MoveSplineFlag splineflags = move_spline.splineflags;
        if (splineflags & MoveSplineFlag::UnCompressedPath)
        {
            if (splineflags.cyclic)
                WriteCatmullRomCyclicPath(spline, data);
            else
                WriteCatmullRomPath(spline, data);
        }
        else
            WriteLinearPath(spline, data);
    }

	void PacketBuilder::WriteBytes(const MoveSpline& move_spline, ByteBuffer& data)
    {
        uint32 nodes = move_spline.getPath().size();

        data.WriteBit(false);
        data.WriteBits(SPLINEFLAG_GLIDE, 25);
        data.WriteBits(SPLINEMODE_LINEAR, 2);
        data.WriteBit(false);
        data.WriteBits(nodes, 22);
        data.WriteBits(SPLINETYPE_NORMAL, 2);

        MoveSplineFlag splineFlags = move_spline.splineflags;

        if (splineFlags.walkmode)
        {
            uint8 guidMask[] = { 7, 3, 4, 2, 1, 6, 0, 5 };
            data.WriteGuidMask(move_spline.facing.target, guidMask, 8);
        }
    }
	
	void PacketBuilder::WriteData(const MoveSpline& move_spline, ByteBuffer& data)
    {
        MoveSplineFlag splineFlags = move_spline.splineflags;
        uint32 nodes = move_spline.getPath().size();

        data.append<Vector3>(&move_spline.getPath()[0], nodes);
        data << float(1.f);                             // splineInfo.duration_mod; added in 3.1

        if (splineFlags.walkmode)
        {
            uint8 guidBytes[] = { 3, 4, 5, 7, 2, 0, 6, 1 };
            data.WriteGuidBytes(move_spline.facing.target, guidBytes, 8, 0);
        }

        if(splineFlags.flying)
            data << move_spline.facing.f.x << move_spline.facing.f.y << move_spline.facing.f.z;

        data << splineFlags.raw();

        if (splineFlags.orientationFixed)
            data << move_spline.facing.angle;

        data << move_spline.timePassed();
        data << move_spline.Duration();
        data << move_spline.GetId();

        data << move_spline.FinalDestination().z;
        data << move_spline.FinalDestination().y;
        data << uint32(0);
        data << move_spline.FinalDestination().x;
    }
    /*void PacketBuilder::WriteCreate(const MoveSpline& move_spline, ByteBuffer& data)
    {
        //WriteClientStatus(mov,data);
        //data.append<float>(&mov.m_float_values[SpeedWalk], SpeedMaxCount);
        //if (mov.SplineEnabled())
        {
            MoveSplineFlag splineFlags = move_spline.splineflags;

            data << splineFlags.raw();

            if (splineFlags.final_angle)
            {
                data << move_spline.facing.angle;
            }
            else if (splineFlags.final_target)
            {
                data << move_spline.facing.target;
            }
            else if(splineFlags.final_point)
            {
                data << move_spline.facing.f.x << move_spline.facing.f.y << move_spline.facing.f.z;
            }

            data << move_spline.timePassed();
            data << move_spline.Duration();
            data << move_spline.GetId();

            data << float(1.f);                             // splineInfo.duration_mod; added in 3.1
            data << float(1.f);                             // splineInfo.duration_mod_next; added in 3.1

            data << move_spline.vertical_acceleration;      // added in 3.1
            data << move_spline.effect_start_time;          // added in 3.1

            uint32 nodes = move_spline.getPath().size();
            data << nodes;
            data.append<Vector3>(&move_spline.getPath()[0], nodes);
            data << uint8(move_spline.spline.mode());       // added in 3.1
            data << (move_spline.isCyclic() ? Vector3::zero() : move_spline.FinalDestination());
        }
    }*/
}
