#include "lua/lua_manager.hpp"

extern "C" __declspec(dllexport) void unload()
{
	big::g_running = false;
}
