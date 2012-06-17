/*
 * Copyright (C) 2011-2012 Project SkyFire <http://www.projectskyfire.org/>
 * Copyright (C) 2008-2012 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2005-2012 MaNGOS <http://getmangos.com/>
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

#ifndef SKYFIRE_WORLDPACKET_H
#define SKYFIRE_WORLDPACKET_H

#include "Common.h"
#include "ByteBuffer.h"

#define SMSG_MULTIPLE_PACKETS_DEF 0x0FEC0 // 4.0.6a 13623 IT WONT TAKE OPCODES HEADER

class WorldPacket : public ByteBuffer
{
    public:
                                                            // just container for later use
        WorldPacket()                                       : ByteBuffer(0), m_opcode(0)
        {
        }
        explicit WorldPacket(uint32 opcode, size_t res = 200, bool hack = false) : ByteBuffer(res), m_opcode(opcode)
        {
            // This is a hack fix.
            // The client will not 'eat' certain opcodes when they're sent under normal circumstances.
            // This is due to the new redirection system implemented by Blizzard in Cataclysm.
            // Another solution to get them handled would be to patch the client even heavier than we already do.
            // In this case, I choose to spread hacks in our code, rather than in Blizzard's
            // - Dvlpr
            if (hack)
            {
                m_opcode = SMSG_MULTIPLE_PACKETS_DEF;
                *this << uint16(opcode);
            }
        }
                                                            // copy constructor
        WorldPacket(const WorldPacket &packet)              : ByteBuffer(packet), m_opcode(packet.m_opcode)
        {
        }

        void Initialize(uint32 opcode, size_t newres = 200, bool hack = false)
        {
            clear();
            _storage.reserve(newres);
            
            if (hack)
            {
                m_opcode = SMSG_MULTIPLE_PACKETS_DEF;
                *this << uint16(opcode);
            }
            else
                m_opcode = opcode;
        }

        uint32 GetOpcode() const { return m_opcode; }
        void SetOpcode(uint32 opcode) { m_opcode = opcode; }

        void compress(uint32 opcode);
    protected:
        uint32 m_opcode;
        void _compress(void* dst, uint32 *dst_size, const void* src, int src_size);
};
#endif
