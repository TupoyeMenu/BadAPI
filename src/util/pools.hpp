/**
 * @file pools.hpp
 * 
 * @copyright GNU General Public License Version 2.
 * This file is part of YimMenu.
 * YimMenu is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 2 of the License, or (at your option) any later version.
 * YimMenu is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License along with YimMenu. If not, see <https://www.gnu.org/licenses/>.
 */

#pragma once
#include "common.hpp"
#include "gta/pointers.hpp"
#include "util/header_wrappers/include_as_enhaced.hpp"
#include "gta/pools.hpp"
#include "util/header_wrappers/include_as_legacy.hpp"
#include "gta/pools.hpp"
#include "util/header_wrappers/clear_include.hpp"

namespace big::pools
{
	inline legacy::rage::fwBasePool* get_all_peds_legacy()
	{
		return *(legacy::rage::fwBasePool**)g_pointers->m_ped_pool;
	}
	inline enhanced::rage::fwBasePool* get_all_peds_enhaced()
	{
		if (((PoolEncryption*)g_pointers->m_ped_pool)->m_IsSet)
		{
			uint64_t x = _rotl64(((PoolEncryption*)g_pointers->m_ped_pool)->m_Second, 30);
			return reinterpret_cast<enhanced::rage::fwBasePool*>(~_rotl64(_rotl64(x ^ ((PoolEncryption*)g_pointers->m_ped_pool)->m_First, 32), ((uint8_t)x & 0x1Fu) + 2));
		}

		return nullptr;
	}

	inline legacy::rage::fwVehiclePool* get_all_vehicles_legacy()
	{
		return **(legacy::rage::fwVehiclePool***)g_pointers->m_vehicle_pool;
	}
	inline enhanced::rage::fwVehiclePool* get_all_vehicles_enhanced()
	{
		return **(enhanced::rage::fwVehiclePool***)g_pointers->m_vehicle_pool;
	}

	inline legacy::rage::fwBasePool* get_all_props_legacy()
	{
		return *(legacy::rage::fwBasePool**)g_pointers->m_prop_pool;
	}
	inline enhanced::rage::fwBasePool* get_all_props_enhaced()
	{
		if (((PoolEncryption*)g_pointers->m_prop_pool)->m_IsSet)
		{
			uint64_t x = _rotl64(((PoolEncryption*)g_pointers->m_prop_pool)->m_Second, 30);
			return reinterpret_cast<enhanced::rage::fwBasePool*>(~_rotl64(_rotl64(x ^ ((PoolEncryption*)g_pointers->m_prop_pool)->m_First, 32), ((uint8_t)x & 0x1Fu) + 2));
		}

		return nullptr;
	}

	inline auto get_all_peds_array()
	{
		std::vector<Entity> arr;
		if(g_is_enhanced)
		{
			auto pool = PoolUtils<rage::fwEntity*, enhanced::rage::fwBasePool>(get_all_peds_enhaced());
			for (auto entity : pool)
			{
				if (entity)
					arr.push_back(big::g_pointers->m_ptr_to_handle(entity));
			}
		}
		else
		{
			auto pool = PoolUtils<rage::fwEntity*, legacy::rage::fwBasePool>(get_all_peds_legacy());
			for (auto entity : pool)
			{
				if (entity)
					arr.push_back(big::g_pointers->m_ptr_to_handle(entity));
			}
		}

		return arr;
	}

	inline auto get_all_vehicles_array()
	{
		std::vector<Entity> arr;
		if(g_is_enhanced)
		{
			auto pool = PoolUtils<rage::fwEntity*, enhanced::rage::fwVehiclePool>(get_all_vehicles_enhanced());
			for (auto entity : pool)
			{
				if (entity)
					arr.push_back(big::g_pointers->m_ptr_to_handle(entity));
			}
		}
		else
		{
			auto pool = PoolUtils<rage::fwEntity*, legacy::rage::fwVehiclePool>(get_all_vehicles_legacy());
			for (auto entity : pool)
			{
				if (entity)
					arr.push_back(big::g_pointers->m_ptr_to_handle(entity));
			}
		}

		return arr;
	}

	inline auto get_all_props_array()
	{
		std::vector<Entity> arr;
		if(g_is_enhanced)
		{
			auto pool = PoolUtils<rage::fwEntity*, enhanced::rage::fwBasePool>(get_all_props_enhaced());
			for (auto entity : pool)
			{
				if (entity)
					arr.push_back(big::g_pointers->m_ptr_to_handle(entity));
			}
		}
		else
		{
			auto pool = PoolUtils<rage::fwEntity*, legacy::rage::fwBasePool>(get_all_props_legacy());
			for (auto entity : pool)
			{
				if (entity)
					arr.push_back(big::g_pointers->m_ptr_to_handle(entity));
			}
		}

		return arr;
	}
};