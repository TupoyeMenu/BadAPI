/**
 * @file byte_patch_manager.cpp
 * 
 * @copyright GNU General Public License Version 2.
 * This file is part of YimMenu.
 * YimMenu is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 2 of the License, or (at your option) any later version.
 * YimMenu is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License along with YimMenu. If not, see <https://www.gnu.org/licenses/>.
 */

#include "byte_patch_manager.hpp"

#include "gta/pointers.hpp"
#include "hooking/hooking.hpp"
#include "memory/byte_patch.hpp"
#include "services/anti_cheat_bypass/anti_cheat_bypass.hpp"
#include "util/explosion_anti_cheat_bypass.hpp"

namespace big
{
	static void init()
	{
		// Patch blocked explosions
		explosion_anti_cheat_bypass::m_can_blame_others =
		    memory::byte_patch::make(g_pointers->m_blame_explode.as<uint16_t*>(), 0xE990).get();
		explosion_anti_cheat_bypass::m_can_use_blocked_explosions =
		    memory::byte_patch::make(g_pointers->m_explosion_patch.as<uint16_t*>(), 0x9090).get();

		if (g_is_enhanced)
		{
			anti_cheat_bypass::m_battleye_status_update_patch =
			    memory::byte_patch::make(g_pointers->m_battleye_status_update_patch, 0xC3).get();
		}
	}

	byte_patch_manager::byte_patch_manager()
	{
		init();

		g_byte_patch_manager = this;
	}

	byte_patch_manager::~byte_patch_manager()
	{
		memory::byte_patch::restore_all();

		g_byte_patch_manager = nullptr;
	}
}