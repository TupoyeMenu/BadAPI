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

#include "hooking.hpp"
#include "memory/byte_patch.hpp"
#include "pointers.hpp"
#include "util/explosion_anti_cheat_bypass.hpp"
#include "util/world_model.hpp"

namespace big
{
	static void init()
	{
		// Patch World Model Spawn Bypass
		std::array<uint8_t, 24> world_spawn_patch;
		std::fill(world_spawn_patch.begin(), world_spawn_patch.end(), 0x90);
		world_model_bypass::m_world_model_spawn_bypass =
		    memory::byte_patch::make(g_pointers->m_world_model_spawn_bypass, world_spawn_patch).get();

		// Patch blocked explosions
		explosion_anti_cheat_bypass::m_can_blame_others =
		    memory::byte_patch::make(g_pointers->m_blame_explode.as<uint16_t*>(), 0xE990).get();
		explosion_anti_cheat_bypass::m_can_use_blocked_explosions =
		    memory::byte_patch::make(g_pointers->m_explosion_patch.sub(12).as<uint16_t*>(), 0x9090).get();
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