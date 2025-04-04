#include "hooking/hooking.hpp"
#include "native_hooks/native_hooks.hpp"
#include "services/script_patcher/script_patcher_service.hpp"

int updates_per_update = 1;

namespace big
{
	void hooks::update_script_threads()
	{
		for(int i = 0; i < updates_per_update; i++)
			g_hooking->get_original<hooks::update_script_threads>()();
	}
}
