#pragma once
#include "gta/net_game_event.hpp"

#include "services/players/player_service.hpp"

namespace big
{
	class packet
	{
	public:
		char m_data[0x480]{};
		rage::datBitBuffer m_buffer;

		packet();
		void send(uint32_t msg_id, bool unk_flag = false);

		inline operator rage::datBitBuffer&()
		{
			return m_buffer;
		}

		template<typename T>
		inline void write(T data, int length)
		{
			m_buffer.Write<T>(data, length);
		}

		inline void seek(int bits)
		{
			m_buffer.Seek(bits);
		}
		inline void write_array_bytes(const void* array, int bytes)
		{
			m_buffer.WriteArrayBytes(array, bytes);
		}

		inline void write_message(rage::eNetMessage message)
		{
			write<int>(0x3246, 14);
			if ((int)message > 0xFF)
			{
				write<bool>(true, 1);
				write<rage::eNetMessage>(message, 16);
			}
			else
			{
				write<bool>(false, 1);
				write<rage::eNetMessage>(message, 8);
			}
		}
	};
}