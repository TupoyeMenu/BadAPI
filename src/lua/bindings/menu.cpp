#include "lua/sol_include.hpp"
#include "version.hpp"

namespace lua::menu
{
	// Lua API: Table
	// Name: menu
	// Functions for interacting with the C++ side of BadAPI.

	// Lua API: Function
	// Table: menu
	// Name: get_dll_path
	// Returns: string: The path to BadAPI.dll
	static sol::object get_dll_path(sol::this_state state_)
	{
		char path[MAX_PATH];
		HMODULE hm = nullptr;

		if (GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, (LPCSTR)&get_dll_path, &hm) == 0)
		{
			int ret = GetLastError();
			LOG(WARNING) << "GetModuleHandle failed, error = " << ret;
			return sol::lua_nil;
		}
		if (GetModuleFileName(hm, path, sizeof(path)) == 0)
		{
			int ret = GetLastError();
			LOG(WARNING) << "GetModuleFileName failed, error = " << ret;
			return sol::lua_nil;
		}
		return sol::make_object(state_, path);
	}

	// Lua API: Function
	// Table: menu
	// Name: get_version_string
	// Returns: string: The version of BadAPI.dll. Example: `0.1.0-beta`
	static std::string get_version()
	{
		return big::version::VERSION;
	}

	void bind(sol::state& state)
	{
		auto ns            = state["menu"].get_or_create<sol::table>();
		ns["get_dll_path"] = get_dll_path;
		ns["get_version"]  = get_version;
	}
}
