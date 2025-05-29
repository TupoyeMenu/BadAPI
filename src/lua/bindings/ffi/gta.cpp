#include "common.hpp"
#include "gta/joaat.hpp"
#include "gta/script/script_mgr.hpp"

extern "C" __declspec(dllexport) bool is_enhanced()
{
	return big::g_is_enhanced;
}

extern "C" __declspec(dllexport) uint32_t joaat(const char* str)
{
	return rage::joaat(str);
}
extern "C" __declspec(dllexport) uint32_t literal_joaat(const char* str)
{
	return rage::literal_joaat(str);
}

extern "C" __declspec(dllexport) void* get_tls_context()
{
	return rage::tlsContext::get();
}

extern "C" __declspec(dllexport) bool script_can_tick()
{
	return big::g_script_mgr.can_tick();
}
