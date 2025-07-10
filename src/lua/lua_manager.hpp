#pragma once
#include "gta/joaat.hpp"
#include "lua_module.hpp"

namespace big
{
	class lua_manager final
	{
	private:
		std::mutex m_module_lock;
		std::shared_ptr<lua_module> m_module;

		folder m_disabled_scripts_folder;
		folder m_scripts_folder;
		folder m_scripts_config_folder;

	public:
		lua_manager(folder scripts_folder, folder scripts_config_folder);
		~lua_manager();

		void load_all_files();
		void load_file(const std::filesystem::path& file_path);
		void unload_module();

		inline const folder& get_scripts_folder() const
		{
			return m_scripts_folder;
		}

		inline const folder& get_scripts_config_folder() const
		{
			return m_scripts_config_folder;
		}

		std::weak_ptr<lua_module> get_module();
		void draw_always_draw_gui();

		void handle_error(const sol::error& error, const sol::state_view& state);

		template<template_str menu_event_, typename Return = void, typename... Args>
		inline std::conditional_t<std::is_void_v<Return>, void, std::optional<Return>> trigger_event(Args&&... args)
		{
			std::lock_guard guard(m_module_lock);

			if (auto vec = m_module->m_event_callbacks.find(rage::joaat(menu_event_.value)); vec != m_module->m_event_callbacks.end())
			{
				for (auto& cb : vec->second)
				{
					auto result = cb.second(args...);

					if (!result.valid())
					{
						handle_error(result, result.lua_state());
						continue;
					}

#ifndef __GNUC__
					if constexpr (!std::is_void_v<Return>)
					{
						if (result.return_count() == 0)
							continue;

						if (!result[0].template is<Return>())
							continue;

						return result[0].template get<Return>();
					}
#endif // __GNUC__
				}
			}

			if constexpr (!std::is_void_v<Return>)
				return std::nullopt;
		}

		inline void for_each_module(auto func)
		{
			std::lock_guard guard(m_module_lock);
			func(m_module);
		}
	};

	inline lua_manager* g_lua_manager;
}
