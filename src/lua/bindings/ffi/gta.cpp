#include "common.hpp"
#include "gta/joaat.hpp"
#include "gta/pointers.hpp"
#include "gta/script/script_mgr.hpp"
#include "gta/gta_util.hpp"

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

extern "C" __declspec(dllexport) uint32_t get_screen_resolution_x()
{
	return *big::g_pointers->m_resolution_x;
}
extern "C" __declspec(dllexport) uint32_t get_screen_resolution_y()
{
	return *big::g_pointers->m_resolution_y;
}

extern "C" __declspec(dllexport) bool queue_packet(rage::netConnectionManager* mgr, int msg_id, void* data, int size, int flags, uint16_t* out_seq_id)
{
	return big::g_pointers->m_queue_packet(mgr, msg_id, data, size, flags, out_seq_id);
}

extern "C" __declspec(dllexport) CNetworkPlayerMgr* get_network_player_mgr()
{
	return big::gta_util::get_network_player_mgr();
}

