#pragma once
#include "memory/byte_patch.hpp"

namespace big
{
	struct old_style_script_event
	{
		inline static memory::byte_patch* m_set_event_hash;
		inline static memory::byte_patch* m_set_player_bits;

		inline static void apply()
		{
			old_style_script_event::m_set_event_hash->apply();
			old_style_script_event::m_set_player_bits->apply();
		}

		inline static void restore()
		{
			old_style_script_event::m_set_event_hash->restore();
			old_style_script_event::m_set_player_bits->restore();
		}
	};
}