/**
 * @file script_vm.cpp
 * 
 * @copyright GNU General Public License Version 2.
 * This file is part of YimMenu.
 * YimMenu is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 2 of the License, or (at your option) any later version.
 * YimMenu is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License along with YimMenu. If not, see <https://www.gnu.org/licenses/>.
 */

#include "gta/pointers.hpp"
#include "hooking/hooking.hpp"
#include "services/script_patcher/script_patcher_service.hpp"

#include <script/scrProgram.hpp>

namespace big
{
	class script_vm_guard
	{
		rage::scrProgram* m_program;
		uint8_t** m_orig_bytecode;

	public:
		script_vm_guard(rage::scrProgram* program) :
		    m_program(program)
		{
			m_orig_bytecode = program->m_code_blocks;
			if (auto bytecode = g_script_patcher_service->get_script_bytecode(program->m_name_hash))
			{
				program->m_code_blocks = bytecode;
			}

			g.in_script_vm = true;
		}

		~script_vm_guard()
		{
			m_program->m_code_blocks = m_orig_bytecode;

			g.in_script_vm = false;
		}
	};

	rage::eThreadState hooks::script_vm(uint64_t* start_stack, uint64_t** scr_globals, rage::scrProgram* program, rage::scrThreadContext* ctx)
	{
		script_vm_guard guard(program);

		auto ret = g_hooking->get_original<hooks::script_vm>()(start_stack, scr_globals, program, ctx);
		return ret;
	}
}