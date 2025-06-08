
#if !POOLS_HPP_LEGACY || !POOLS_HPP_ENHANCED
	#if ENHANCED
		#define POOLS_HPP_ENHANCED 1
	#else
		#define POOLS_HPP_LEGACY 1
	#endif

	#include "player/CNonPhysicalPlayerData.hpp"
	#include "rage/rlGamerInfo.hpp"

namespace GAME_BRANCH
{
	namespace rage
	{
	#pragma pack(push, 8)
		class netPlayer
		{
		public:
			DEFINE_RAGE_RTTI(netPlayer)

			virtual void Reset();
			virtual bool IsPhysical();
			virtual const char* GetName();
			virtual std::uint64_t GetHostToken();
			virtual void UpdatePermissions(); // dev status, comm perms, etc.
			virtual bool IsHost();
			virtual ::rage::rlGamerInfo* GetGamerInfo();
			virtual void UpdateUnk(); // force updates a player ped data node

			int m_AccountId;      // -- added b3504
			int64_t m_RockstarId; // -- added b3504
	#if ENHANCED
			char pad_0018[0x38]; // voice chat stuff
	#else
			char new_0018[0x90]; // -- added b3504
			uint32_t m_player_type;
	#endif
			CNonPhysicalPlayerData* m_NonPhysicalPlayer;
			uint32_t m_MessageId;
			char pad_001C[4];
			uint8_t m_ActiveIndex;
			uint8_t m_PlayerIndex;
	#if ENHANCED
			char pad_0062[0x6E];
			uint8_t m_Flags;
			char pad_0091[0xF];
	#else
			char pad_0022[3];
			uint16_t m_complaints;
			char pad_0027[17];
			class CNetGamePlayer* m_unk_net_player_list[10];
			char pad_0090[4];
			uint64_t pad_0098;
	#endif
		};
	#pragma pack(pop)
	}

	class CNetGamePlayer : public rage::netPlayer
	{
	public:
		void* m_Unk;
		CPlayerInfo* m_PlayerInfo;
	};

}

#endif
