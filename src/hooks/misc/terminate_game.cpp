#include "hooking/hooking.hpp"

namespace big
{
	void hooks::terminate_game(int p1)
	{
		LOG(WARNING) << "Game has decided to terminate " << p1 << " Called from: " << _ReturnAddress();
		*((volatile uint64_t*)0) = 0xDEADBEEF; // Trigger a crash to get a log.

		g_hooking->get_original<hooks::terminate_game>()(p1);
	}
}