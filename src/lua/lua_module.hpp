#pragma once
#include "bindings/gui.hpp"
#include "core/data/menu_event.hpp"
#include "gta/script/script.hpp"
#include "lua/bindings/scr_patch.hpp"
#include "lua_patch.hpp"

namespace big
{
	class lua_module
	{
		sol::state m_state;

		sol::protected_function m_io_open;

		std::filesystem::path m_module_path;

		std::string m_module_name;
		rage::joaat_t m_module_id;

		bool m_disabled;
		std::mutex m_registered_scripts_mutex;

	public:
		std::unordered_map<rage::joaat_t, std::unique_ptr<script>> m_registered_scripts;
		std::vector<std::unique_ptr<lua_patch>> m_registered_patches;
		std::vector<std::unique_ptr<lua::scr_patch::scr_patch>> m_registered_script_patches;

		std::unordered_map<menu_event, std::unordered_map<rage::joaat_t, sol::protected_function>> m_event_callbacks;
		std::vector<void*> m_allocated_memory;

		lua_module(const std::filesystem::path& module_path, folder& scripts_folder, bool disabled = false);
		~lua_module();

		const std::filesystem::path& module_path() const;

		rage::joaat_t module_id() const;
		const std::string& module_name() const;
		const bool is_disabled() const;

		// used for sandboxing and limiting to only our custom search path for the lua require function
		void set_folder_for_lua_require(folder& scripts_folder);

		void sandbox_lua_os_library();
		void sandbox_lua_io_library();
		void sandbox_lua_loads(folder& scripts_folder);

		void init_lua_api(folder& scripts_folder);

		void load_and_call_script(const std::filesystem::path& file_path);

		inline void for_each_script(auto func)
		{
			std::lock_guard guard(m_registered_scripts_mutex);

			for (auto& script : m_registered_scripts)
			{
				func(script.second.get());
			}
		}

		void tick_scripts();
		void cleanup_done_scripts();
	};
}