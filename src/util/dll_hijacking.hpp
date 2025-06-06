#pragma once
#include "memory/module.hpp"

#include <cstring>
#include <string_view>
#include <winternl.h>

namespace big
{
	inline bool is_dll_hijacked(std::wstring dll_name)
	{
		const auto peb = reinterpret_cast<PPEB>(NtCurrentTeb()->ProcessEnvironmentBlock);
		if (!peb)
			return false;

		const auto ldr_data = peb->Ldr;
		if (!ldr_data)
			return false;

		const auto module_list = &ldr_data->InMemoryOrderModuleList;
		auto module_entry      = module_list->Flink;
		int num_modules = 0;
		for (; module_list != module_entry; module_entry = module_entry->Flink)
		{
			const auto tableEntry = CONTAINING_RECORD(module_entry, LDR_DATA_TABLE_ENTRY, InMemoryOrderLinks);
			if (!tableEntry)
				continue;

			if (dll_name == tableEntry->FullDllName.Buffer)
			{
				num_modules++;
			}
		}
		return num_modules > 1;
	}
}

