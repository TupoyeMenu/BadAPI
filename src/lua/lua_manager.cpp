#include "lua_manager.hpp"

#include "file_manager/file_manager.hpp"
#include "lua/sol_include.hpp"

#include <filesystem>

#define LIBARCHIVE_STATIC 1

#include <archive.h>
#include <archive_entry.h>

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
		{
			if (entry.is_regular_file() && entry.path().extension() == ".lua")
				load_file(entry.path());
			if (entry.is_regular_file() && entry.path().extension() == ".zip")
			{
				if (std::filesystem::exists(entry.path().parent_path() / entry.path().stem()))
					LOG(WARNING) << "There is a directory and an archive with the same name, not loading the archive.";
				else
					load_archive(entry.path());
			}
		}
	}

	void lua_manager::unload_module()
	{
		std::lock_guard guard(m_module_lock);
		m_module.reset();
	}

	void lua_manager::load_file(const std::filesystem::path& file_path, const std::string_view& content)
	{
		// Some scripts are library scripts, they do nothing on their own and are intended to be used with require, they take up space in the script list for no reason.
		if (file_path.wstring().contains(L"includes"))
			return;

		std::lock_guard guard(m_module_lock);
		m_module->load_and_call_script(file_path, content);
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

		std::lock_guard guard(m_module_lock);

		const auto rel                = relative(file_path, m_disabled_scripts_folder.get_path());
		const auto is_disabled_module = !rel.empty() && rel.native()[0] != '.';
		if (!is_disabled_module)
		{
			m_module->load_and_call_script(file_path);
		}
	}

	void lua_manager::load_archive(const std::filesystem::path& file_path)
	{
		if (!std::filesystem::exists(file_path))
		{
			LOG(WARNING) << reinterpret_cast<const char*>(file_path.u8string().c_str()) << " does not exist in the filesystem. Not loading it.";
			return;
		}

		struct archive* a;
		struct archive_entry* entry;
		int r;

		a = archive_read_new();
		archive_read_support_filter_all(a);
		archive_read_support_format_all(a);
		r = archive_read_open_filename(a, reinterpret_cast<const char*>(file_path.u8string().c_str()), 10240);
		if (r != ARCHIVE_OK)
		{
			LOG(FATAL) << reinterpret_cast<const char*>(file_path.u8string().c_str()) << " Failed to load";
			return;
		}


		while (archive_read_next_header(a, &entry) == ARCHIVE_OK)
		{
			size_t file_size = archive_entry_size(entry);
			std::filesystem::path path(archive_entry_pathname(entry));

			char* buf = new char[file_size];

			int64_t bytes_read = archive_read_data(a, buf, file_size);

			if (bytes_read < 0)
			{
				LOG(VERBOSE) << "Failed to read file: " << path.string() << " - " << archive_error_string(a);
				continue;
			}

			if (path.extension() != ".lua" || archive_entry_filetype(entry) == AE_IFDIR)
				continue;

			load_file(path.filename().string(), std::string(buf, file_size));

			delete[] buf;
		}

		r = archive_read_free(a);
		if (r != ARCHIVE_OK)
			LOG(FATAL) << reinterpret_cast<const char*>(file_path.u8string().c_str()) << " Failed to close";
	}

	std::weak_ptr<lua_module> lua_manager::get_module()
	{
		return m_module;
	}
}
