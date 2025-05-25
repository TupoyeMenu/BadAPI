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
		inline void SC_TRANSITION_NEWS_SHOW(rage::scrNativeCallContext* src)
		{
			src->set_return_value<BOOL>(SOCIALCLUB::SC_TRANSITION_NEWS_SHOW(src->get_arg<Any>(0)));
		}

		inline void SC_TRANSITION_NEWS_SHOW_TIMED(rage::scrNativeCallContext* src)
		{
			src->set_return_value<BOOL>(SOCIALCLUB::SC_TRANSITION_NEWS_SHOW_TIMED(src->get_arg<Any>(0), src->get_arg<Any>(0)));
		}

		inline int get_new_stack_size(int stack_size)
		{
			// TODO: Use ranges instead of exact numbers
			switch (stack_size)
			{
			case 3200:
				return 3800; // SHOP_CONTROLLER
			case 20000:
			case 21000: // 2545
			case 23000: // 2699
			case 24000: // 2802
			case 26000: // 3095
				return 27000; // FMMC_LAUNCHER
			case 33500: // 2545
			case 33750: // GTA source
				return 34750;
			//case 34750: // ? Wtf is this from ?
			//case 35500: // 2612
			//	return 37500; // MP_LAUNCH_SCRIPT
			case 51000:
			case 54000: // 2802
			case 57500: // 2944
			case 60500: // 3095
			case 62500: // 3258
				return 63500; // MISSION
			case 66000: // 2612
			case 68500: // 2699
			case 70500: // GTA source
			case 72500: // 2802
			case 80000: // 2944
			case 82500: // 3095
			case 85000: // 3258
				return 87500; // MULTIPLAYER_FREEMODE
			default: return stack_size;
			}
		}

		inline void START_NEW_SCRIPT(rage::scrNativeCallContext* src)
		{
			const char* name = src->get_arg<const char*>(0);
			int stack_size = src->get_arg<int>(1);

			LOGF(VERBOSE, "START_NEW_SCRIPT({}, {})", name, stack_size);
			
			src->set_return_value(BUILTIN::START_NEW_SCRIPT(name, get_new_stack_size(stack_size)));
		}
		inline void START_NEW_SCRIPT_WITH_NAME_HASH(rage::scrNativeCallContext* src)
		{
			Hash name = src->get_arg<Hash>(0);
			int stack_size = src->get_arg<int>(1);

			LOGF(VERBOSE, "START_NEW_SCRIPT_WITH_NAME_HASH({}, {})", name, stack_size);
			
			src->set_return_value(BUILTIN::START_NEW_SCRIPT_WITH_NAME_HASH(name, get_new_stack_size(stack_size)));
		}
		inline void START_NEW_SCRIPT_WITH_ARGS(rage::scrNativeCallContext* src)
		{
			const char* name = src->get_arg<const char*>(0);
			int stack_size = src->get_arg<int>(3);

			LOGF(VERBOSE, "START_NEW_SCRIPT_WITH_ARGS({}, {})", name, stack_size);

			src->set_return_value(BUILTIN::START_NEW_SCRIPT_WITH_ARGS(name, src->get_arg<Any*>(1), src->get_arg<int>(2), get_new_stack_size(stack_size)));
		}
		inline void START_NEW_SCRIPT_WITH_NAME_HASH_AND_ARGS(rage::scrNativeCallContext* src)
		{
			Hash name = src->get_arg<Hash>(0);
			int stack_size = src->get_arg<int>(3);

			LOGF(VERBOSE, "START_NEW_SCRIPT_WITH_NAME_HASH_AND_ARGS({}, {})", name, stack_size);

			src->set_return_value(BUILTIN::START_NEW_SCRIPT_WITH_NAME_HASH_AND_ARGS(name, src->get_arg<Any*>(1), src->get_arg<int>(2), get_new_stack_size(stack_size)));
		}

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