/**
 * @file all_scripts.hpp
 * 
 * @copyright GNU General Public License Version 2.
 * This file is part of YimMenu.
 * YimMenu is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 2 of the License, or (at your option) any later version.
 * YimMenu is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License along with YimMenu. If not, see <https://www.gnu.org/licenses/>.
 */

#pragma once
#include "gta/enums.hpp"
#include "gta/script/fiber_pool.hpp"
#include "gta/script/natives.hpp"
#include "native_hooks.hpp"
#include "util/scripts.hpp"

namespace big
{
	namespace all_scripts
	{
		inline void RETURN_EMPTY_STRING(rage::scrNativeCallContext* src)
		{
			src->set_return_value<const char*>("");
		}

		inline void RETURN_TRUE(rage::scrNativeCallContext* src)
		{
			src->set_return_value<BOOL>(TRUE);
		}

		inline void RETURN_FALSE(rage::scrNativeCallContext* src)
		{
			src->set_return_value<BOOL>(FALSE);
		}

		inline void DO_NOTHING(rage::scrNativeCallContext* src)
		{
		}
	}
}