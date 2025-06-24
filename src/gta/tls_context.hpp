#if !TLS_CONTEXT_HPP_LEGACY || !TLS_CONTEXT_HPP_ENHANCED
	#if ENHANCED
		#define TLS_CONTEXT_HPP_ENHANCED 1
	#else
		#define TLS_CONTEXT_HPP_LEGACY 1
	#endif

	#include <intrin.h>

namespace GAME_BRANCH
{
	namespace rage
	{
	#pragma pack(push, 1)
		class tlsContext
		{
		public:
	#if ENHANCED
			char m_Pad1[0x7A0];
	#else
			char m_Pad1[0x2A50];
	#endif
			void* m_script_thread;
			bool m_is_script_thread_active;

			static tlsContext* get()
			{
				constexpr std::uint32_t TlsIndex = 0x0;
				return *reinterpret_cast<tlsContext**>(__readgsqword(0x58) + TlsIndex);
			}
		};
	#pragma pack(pop)
	}
}

#endif