#include "gta/joaat.hpp"
#include "lua/lua_manager.hpp"
#include "lua/sol_include.hpp"
#include "util/filesystem.hpp"

namespace lua::global_table
{
	// Lua API: Table
	// Name: Global Table
	// Custom fields, functions, etc added to The Lua [Global Table](https://www.lua.org/pil/15.4.html).

	// Lua API: Function
	// Table: Global Table
	// Name: joaat
	// Param: str: string: The string that needs to be joaat hashed.
	// Returns: integer: The joaat hashed input string.

	static void include(const std::string& filename)
	{
		const auto scripts_path = big::filesystem::make_absolute(big::g_lua_manager->get_scripts_folder().get_path(), filename);
		if (!scripts_path)
		{
			LOG(WARNING) << "dofile is restricted to the scripts folder, and the filename provided (" << filename << ") is outside of it.";
		}
		else
		{
			big::g_lua_manager->get_module().lock()->load_and_call_script(scripts_path.value());
		}
	};

	// Lua API: Function
	// Table: Global Table
	// Name: get_dll_path
	// Returns: string: The path to the DLL of whatever this is.
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

	ImVec4 vec4_array[ImGuiCol_COUNT];

	void bind(sol::state& state)
	{
		state["joaat"]         = rage::joaat;
		state["literal_joaat"] = rage::literal_joaat;
		state["include"]       = include;
		state["dofile"]        = include;
		state["get_dll_path"]  = get_dll_path;

		state["vec4_array"]  = &vec4_array;
	}
}
