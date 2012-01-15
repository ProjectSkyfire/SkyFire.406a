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

#include "Common.h"
#include "ByteBuffer.h"
#include "WorldPacket.h"
#include "UpdateData.h"
#include "Log.h"
#include "Opcodes.h"
#include "World.h"
#include "zlib.h"

UpdateData::UpdateData(uint16 map) : m_map(map), m_blockCount(0) {}

void UpdateData::AddOutOfRangeGUID(std::set<uint64>& guids)
{
    m_outOfRangeGUIDs.insert(guids.begin(), guids.end());
}

void UpdateData::AddOutOfRangeGUID(uint64 guid)
{
    m_outOfRangeGUIDs.insert(guid);
}

void UpdateData::AddUpdateBlock(const ByteBuffer &block)
{
    m_data.append(block);
    ++m_blockCount;
}

bool UpdateData::BuildPacket(WorldPacket *packet)
{
    ASSERT(packet->empty());                                // shouldn't happen

    ByteBuffer buf(2 + 4 + (m_outOfRangeGUIDs.empty() ? 0 : 1 + 4 + 9 * m_outOfRangeGUIDs.size()) + m_data.wpos());

    buf << uint16(m_map);
    buf << uint32(!m_outOfRangeGUIDs.empty() ? m_blockCount + 1 : m_blockCount);

    if (!m_outOfRangeGUIDs.empty())
    {
        buf << uint8(UPDATETYPE_OUT_OF_RANGE_OBJECTS);
        buf << uint32(m_outOfRangeGUIDs.size());

        for (std::set<uint64>::const_iterator i = m_outOfRangeGUIDs.begin(); i != m_outOfRangeGUIDs.end(); ++i)
        {
            buf.appendPackGUID(*i);
        }
    }

    buf.append(m_data);

    // Disabled
    /*
    size_t pSize = buf.wpos();                             // use real used data size

    if (pSize > 100)                                       // compress large packets
    {
        uint32 destsize = compressBound(pSize);
        packet->resize(destsize + sizeof(uint32));

        packet->put<uint32>(0, pSize);
        Compress(const_cast<uint8*>(packet->contents()) + sizeof(uint32), &destsize, (void*)buf.contents(), pSize);
        if (destsize == 0)
            return false;

        packet->resize(destsize + sizeof(uint32));
        packet->SetOpcode(SMSG_COMPRESSED_UPDATE_OBJECT);
    }
    else                                                    // send small packets without compression
    {*/
        packet->append(buf);
        packet->SetOpcode(SMSG_UPDATE_OBJECT);
    //}

    return true;
}

void UpdateData::Clear()
{
    m_data.clear();
    m_outOfRangeGUIDs.clear();
    m_blockCount = 0;
    m_map = 0;
}
