#include "anti_cheat_bypass.hpp"
#include "common.hpp"
#include "gta/pointers.hpp"
#include "util/dll_hijacking.hpp"
#include "gta/script/natives.hpp"
#include "gta/script/script.hpp"

using FnGetVersion = int(*)();
using FnLocalSaves = bool(*)();
using FnBattlEyeBypass = bool(*)();

namespace big
{
	void anti_cheat_bypass::run_script_internal()
	{
		if(!g_is_enhanced)
			return;

		m_fsl_loaded = is_dll_hijacked(L"WINMM.dll");
		m_battleye_running = (NETWORK::_NETWORK_GET_GAME_RESTART_REASON() == 0 && GetModuleHandleA("BEClient_x64.dll")) && !m_fsl_loaded;

		const char* mode = "Vanilla";

		if (m_battleye_running)
			mode = "Legit BattlEye";
		else if (m_fsl_loaded)
			mode = "FSL";
	
		LOGF(VERBOSE, "Anticheat bypass mode: {}", mode);

		if (m_fsl_loaded)
		{
			HMODULE hFSL = GetModuleHandleA("WINMM.dll");
			if (hFSL)
			{
				auto LawnchairGetVersion = reinterpret_cast<FnGetVersion>(GetProcAddress(hFSL, "LawnchairGetVersion"));
				auto LawnchairIsProvidingLocalSaves = reinterpret_cast<FnLocalSaves>(GetProcAddress(hFSL, "LawnchairIsProvidingLocalSaves"));
				auto LawnchairIsProvidingBattlEyeBypass = reinterpret_cast<FnBattlEyeBypass>(GetProcAddress(hFSL, "LawnchairIsProvidingBattlEyeBypass"));

				if (LawnchairGetVersion && LawnchairIsProvidingLocalSaves && LawnchairIsProvidingBattlEyeBypass)
				{
					m_fsl_version         = LawnchairGetVersion();
					m_fsl_provides_local_saves = LawnchairIsProvidingLocalSaves();
					m_fsl_provides_be_bypass   = LawnchairIsProvidingBattlEyeBypass();

					LOGF(VERBOSE, "FSL Version: {}", m_fsl_version);
					LOGF(VERBOSE, "FSL Local Saves: {}", m_fsl_provides_local_saves ? "Enabled" : "Disabled");
					LOGF(VERBOSE, "FSL BE Bypass: {}", m_fsl_provides_be_bypass ? "Enabled" : "Disabled");
				}
				else
				{
					LOGF(WARNING, "FSL detected but required exports were missing.");
				}
			}
		}

		if (m_battleye_running)
			LOGF(WARNING, "If you are not running an actual BattlEye bypass, exit the game immediately and ensure that BE is properly disabled");

		if (!m_fsl_provides_be_bypass)
			m_battleye_status_update_patch->apply();

		while (true)
		{
			if (!m_fsl_provides_be_bypass)
			{
				*g_pointers->m_be_restart_status = 0;
				*g_pointers->m_needs_be_restart = false;
				*g_pointers->m_is_be_banned = false;
			}
			script::get_current()->yield();
		}
	}
}