#include "lua_manager.hpp"

#include "file_manager/file_manager.hpp"
#include "lua/sol_include.hpp"

namespace big
{
	std::optional<std::filesystem::path> move_file_relative_to_folder(const std::filesystem::path& original, const std::filesystem::path& target, const std::filesystem::path& file)
	{
		// keeps folder hierarchy intact
		const auto new_module_path = target / relative(file, original);
		g_file_manager.ensure_file_can_be_created(new_module_path);

		try
		{
			rename(file, new_module_path);
		}
		catch (const std::filesystem::filesystem_error& e)
		{
			LOG(FATAL) << "Failed to move Lua file: " << e.what();

			return std::nullopt;
		}
		return {new_module_path};
	}

	lua_manager::lua_manager(folder scripts_folder, folder scripts_config_folder) :
	    m_scripts_folder(scripts_folder),
	    m_scripts_config_folder(scripts_config_folder),
	    m_disabled_scripts_folder(scripts_folder.get_folder("./disabled"))
	{
		m_module = std::make_shared<lua_module>("main", m_scripts_folder, false);

		load_file(m_scripts_folder.get_path() / "core" / "init.lua");

		g_lua_manager = this;

		load_all_files();

		trigger_event<"LuaInitFinished">();
	}

	lua_manager::~lua_manager()
	{
		unload_module();

		g_lua_manager = nullptr;
	}

	void lua_manager::load_all_files()
	{
		for (const auto& entry : std::filesystem::recursive_directory_iterator(m_scripts_folder.get_path(), std::filesystem::directory_options::skip_permission_denied))
			if (entry.is_regular_file() && entry.path().extension() == ".lua")
				load_file(entry.path());
	}

	void lua_manager::unload_module()
	{
		std::lock_guard guard(m_module_lock);
		m_module.reset();
	}

	void lua_manager::load_file(const std::filesystem::path& file_path)
	{
		if (!std::filesystem::exists(file_path))
		{
			LOG(WARNING) << reinterpret_cast<const char*>(file_path.u8string().c_str()) << " does not exist in the filesystem. Not loading it.";
			return;
		}

		// Some scripts are library scripts, they do nothing on their own and are intended to be used with require, they take up space in the script list for no reason.
		if (std::filesystem::relative(file_path.parent_path(), m_scripts_folder.get_path()).wstring().contains(L"includes"))
			return;

		const auto module_name = file_path.filename().string();
		const auto id          = rage::joaat(module_name);

		std::lock_guard guard(m_module_lock);

		const auto rel                = relative(file_path, m_disabled_scripts_folder.get_path());
		const auto is_disabled_module = !rel.empty() && rel.native()[0] != '.';
		if(!is_disabled_module)
		{
			m_module->load_and_call_script(file_path);
		}
	}

	std::weak_ptr<lua_module> lua_manager::get_module()
	{
		return m_module;
	}

	void lua_manager::handle_error(const sol::error& error, const sol::state_view& state)
	{
	}
}
