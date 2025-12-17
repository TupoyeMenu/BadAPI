#pragma once
#include "memory/byte_patch.hpp"
#include "thread_pool.hpp"

namespace big
{
	class anti_cheat_bypass
	{
	public:
		explicit anti_cheat_bypass() = default;
		~anti_cheat_bypass()         = default;
		static void init()
		{
			g_thread_pool->push([] {
				get_instance().run_internal();
			});
		}

		static bool is_fsl_loaded()
		{
			return get_instance().m_fsl_loaded;
		}

		// actual battleye, as opposed to the FSL shim
		static bool is_battleye_running()
		{
			return get_instance().m_battleye_running;
		}
		static bool get_fsl_version()
		{
			return get_instance().m_fsl_version;
		}
		static bool is_fsl_providing_local_saves()
		{
			return get_instance().m_fsl_provides_local_saves;
		}
		static bool is_fsl_providing_be_bypass()
		{
			return get_instance().m_fsl_provides_be_bypass;
		}

	private:
		static anti_cheat_bypass& get_instance()
		{
			static anti_cheat_bypass instance;
			return instance;
		}

		void run_internal();


		bool m_fsl_loaded = false;
		bool m_battleye_running = false;
		int m_fsl_version = -1;
		bool m_fsl_provides_local_saves = false;
		bool m_fsl_provides_be_bypass = false;
	};
}