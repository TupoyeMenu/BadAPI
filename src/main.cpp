/**
 * @file main.cpp
 * @brief File with the DllMain function, used for initialization.
 */

#include "backend/backend.hpp"
#include "backend/byte_patch_manager.hpp"
#include "common.hpp"
#include "file_manager/file_manager.hpp"
#include "gta/joaat.hpp"
#include "gta/pointers.hpp"
#include "gta/script/big_program.hpp"
#include "gta/script/fiber_pool.hpp"
#include "gta/script/invoker.hpp"
#include "gta/script/script_mgr.hpp"
#include "gui/gui.hpp"
#include "hooking/hooking.hpp"
#include "logger/exception_handler.hpp"
#include "lua/lua_manager.hpp"
#include "native_hooks/native_hooks.hpp"
#include "renderer/renderer.hpp"
#include "renderer/renderer_dx11.hpp"
#include "renderer/renderer_dx12.hpp"
#include "services/anti_cheat_bypass/anti_cheat_bypass.hpp"
#include "services/players/player_service.hpp"
#include "services/script_patcher/script_patcher_service.hpp"
#include "services/tunables/tunables_service.hpp"
#include "thread_pool.hpp"
#include "util/is_enhanced.hpp"

#include <memory>
#include <rage/gameSkeleton.hpp>

BOOL APIENTRY DllMain(HMODULE hmod, DWORD reason, PVOID)
{
	using namespace big;
	if (reason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(hmod);

		g_is_enhanced = big::is_enhanced();

		g_hmodule     = hmod;
		g_main_thread = CreateThread(
		    nullptr,
		    0,
		    [](PVOID) -> DWORD {
			    auto handler = exception_handler();
			    std::srand(std::chrono::system_clock::now().time_since_epoch().count());

			    LPCSTR lpClassName = g_is_enhanced ? "sgaWindow" : "grcWindow";
			    while (!FindWindow(lpClassName, nullptr))
				    std::this_thread::sleep_for(1s);

			    wchar_t gta_path[MAX_PATH];
			    GetModuleFileNameW(NULL, gta_path, sizeof(gta_path));

			    std::filesystem::path base_dir = std::filesystem::path(gta_path).parent_path();
			    base_dir /= PROJECT_NAME;
			    g_file_manager.init(base_dir);
			    g_log.initialize(PROJECT_NAME, g_file_manager.get_project_file("./cout.log"));
			    LOG(INFO) << R"kek(
 ______  _       ______                        ______  
(____  \(_)     (____  \                      (_____ \
 ____)  )_  ____ ____)  ) ____  ___  ____ _   _ ____) )
|  __  (| |/ _  |  __  ( / _  |/___)/ _  ) | | /_____/ 
| |__)  ) ( ( | | |__)  | ( | |___ ( (/ / \ V /_______ 
|______/|_|\_|| |______/ \_||_(___/ \____) \_/(_______)
          (_____|)kek";

			    auto thread_pool_instance = std::make_unique<thread_pool>();
			    LOG(INFO) << "Thread pool initialized.";

			    g.init(g_file_manager.get_project_file("./settings.json"));
			    LOG(INFO) << "Settings Loaded.";

			    auto pointers_instance = std::make_unique<pointers>();
			    LOG(INFO) << "Pointers initialized.";

			    auto byte_patch_manager_instance = std::make_unique<byte_patch_manager>();
			    LOG(INFO) << "Byte Patch Manager initialized.";

			    std::unique_ptr<renderer_dx11> dx11_renderer_instance;
			    std::unique_ptr<renderer_dx12> dx12_renderer_instance;
			    if (g_is_enhanced)
			    {
				    while (!*g_pointers->m_resolution_x)
				    {
					    std::this_thread::sleep_for(1s);
				    }
				    dx12_renderer_instance = std::make_unique<renderer_dx12>();
			    }
			    else
			    {
				    dx11_renderer_instance = std::make_unique<renderer_dx11>();
			    }
			    LOG(INFO) << "Renderer initialized.";
			    auto gui_instance = std::make_unique<gui>();

			    auto script_program_instance = std::make_unique<big_program>("BadAPIInternal");
			    create_script_thread("BadAPIInternal");
			    LOG(INFO) << "Script Program initialized.";

			    auto fiber_pool_instance = std::make_unique<fiber_pool>(10);
			    LOG(INFO) << "Fiber pool initialized.";

			    auto hooking_instance = std::make_unique<hooking>();
			    LOG(INFO) << "Hooking initialized.";

			    auto player_service_instance         = std::make_unique<player_service>();
			    auto tunables_service_instance       = std::make_unique<tunables_service>();
			    auto script_patcher_service_instance = std::make_unique<script_patcher_service>();
			    LOG(INFO) << "Script Patcher initialized.";

			    anti_cheat_bypass::init();
			    g_script_mgr.add_script(std::make_unique<script>(&backend::loop, "backend"));
			    g_script_mgr.add_script(std::make_unique<script>(&gui::script_func, "gui"));
			    LOG(INFO) << "Scripts registered.";

			    g_hooking->enable();
			    LOG(INFO) << "Hooking enabled.";

			    auto native_hooks_instance = std::make_unique<native_hooks>();
			    LOG(INFO) << "Dynamic native hooker initialized.";

			    while (!*g_pointers->m_natives_registered)
				    std::this_thread::sleep_for(50ms);

			    g_native_invoker.cache_handlers();
			    LOG(INFO) << "Native handlers cached.";

			    auto lua_manager_instance =
			        std::make_unique<lua_manager>(g_file_manager.get_project_folder("scripts"), g_file_manager.get_project_folder("scripts_config"));
			    LOG(INFO) << "Lua manager initialized.";

			    while (g_running)
				    std::this_thread::sleep_for(500ms);

			    g_hooking->disable();
			    LOG(INFO) << "Hooking disabled.";

			    g_script_mgr.remove_all_scripts();
			    LOG(INFO) << "Scripts unregistered.";

			    lua_manager_instance.reset();
			    LOG(INFO) << "Lua manager uninitialized.";

			    // cleans up the thread responsible for saving settings
			    g.destroy();

			    // Make sure that all threads created don't have any blocking loops
			    // otherwise make sure that they have stopped executing
			    thread_pool_instance->destroy();
			    LOG(INFO) << "Destroyed thread pool.";

			    tunables_service_instance.reset();
			    LOG(INFO) << "Tunables Service reset.";
			    script_patcher_service_instance.reset();
			    LOG(INFO) << "Script Patcher Service reset.";
			    player_service_instance.reset();
			    LOG(INFO) << "Player Service reset.";

			    hooking_instance.reset();
			    LOG(INFO) << "Hooking uninitialized.";

			    native_hooks_instance.reset();
			    LOG(INFO) << "Dynamic native hooker uninitialized.";

			    fiber_pool_instance.reset();
			    LOG(INFO) << "Fiber pool uninitialized.";

			    destroy_script_thread();
			    script_program_instance.reset();
			    LOG(INFO) << "Script Program uninitialized.";

			    dx12_renderer_instance.reset();
			    dx11_renderer_instance.reset();
			    LOG(INFO) << "Renderer uninitialized.";

			    byte_patch_manager_instance.reset();
			    LOG(INFO) << "Byte Patch Manager uninitialized.";

			    pointers_instance.reset();
			    LOG(INFO) << "Pointers uninitialized.";

			    LOG(INFO) << "Farewell!";
			    g_log.destroy();

			    CloseHandle(g_main_thread);
			    FreeLibraryAndExitThread(g_hmodule, 0);
		    },
		    nullptr,
		    0,
		    &g_main_thread_id);
	}

	return true;
}
