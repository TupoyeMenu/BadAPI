/**
 * @file pools.hpp
 * @brief Pool Interator class to iterate over pools. Has just enough operators defined to be able to be used in a for loop, not suitable for any other iterating.
 * @note everything pasted from https://github.com/gta-chaos-mod/ChaosModV/blob/master/ChaosMod/Util/EntityIterator.h
 * Thanks to menyoo for most of these!!
 */


#if !POOLS_HPP_LEGACY && !POOLS_HPP_ENHANCED

template<typename Wrapper, typename PoolType>
class PoolIterator
{
public:
	PoolType* m_Pool = nullptr;
	uint32_t m_Index = 0;

	explicit PoolIterator(PoolType* pool, int32_t index = 0)
	{
		this->m_Pool  = pool;
		this->m_Index = index;
	}

	PoolIterator& operator++()
	{
		for (m_Index++; m_Index < m_Pool->m_Size; m_Index++)
		{
			if (m_Pool->IsValid(m_Index))
			{
				return *this;
			}
		}

		m_Index = m_Pool->m_Size;
		return *this;
	}

	Wrapper operator*()
	{
		auto addr = reinterpret_cast<void*>(m_Pool->GetAt(m_Index));
		return Wrapper(addr);
	}

	bool operator!=(const PoolIterator& other) const
	{
		return this->m_Index != other.m_Index;
	}
};

// Common functions for VehiclePool and GenericPool
template<typename Wrapper, typename PoolType>
class PoolUtils
{
	PoolType* m_Pool;

public:
	PoolUtils(PoolType* pool) :
	    m_Pool(pool)
	{
	}

	auto begin()
	{
		return ++PoolIterator<Wrapper, PoolType>(m_Pool, -1);
	}

	auto end()
	{
		return ++PoolIterator<Wrapper, PoolType>(m_Pool, m_Pool->m_Size);
	}

	auto size()
	{
		return m_Pool->m_Size;
	}
};

#endif

#if !POOLS_HPP_LEGACY || !POOLS_HPP_ENHANCED
	#if ENHANCED
		#define POOLS_HPP_ENHANCED 1
	#else
		#define POOLS_HPP_LEGACY 1
	#endif

	#if ENHANCED
// of all the things they backported from RDR this is probably the dumbest
class PoolEncryption
{
public:
	bool m_IsSet;      //0x0000
	uint64_t m_First;  //0x0008
	uint64_t m_Second; //0x0010
}; //Size: 0x0018
static_assert(sizeof(PoolEncryption) == 0x18);
	#endif

namespace GAME_BRANCH
{
	namespace rage
	{
		class fwBasePool
		{
		public:
	#if ENHANCED
			virtual ~fwBasePool() = 0; // 0x0000
	#endif
			uintptr_t m_Entries;      // 0x0008
			uint8_t* m_Flags;         // 0x0010
			uint32_t m_Size;          // 0x0018
			uint32_t m_ItemSize;      // 0x001C
			uint32_t m_NextSlotIndex; // 0x0020
			uint32_t m_0024;          // 0x0024
			uint32_t m_FreeSlotIndex; // 0x0028

			bool Full() const
			{
				return m_Size - (m_FreeSlotIndex & 0x3FFFFFFF) <= 256;
			}

			int64_t GetNumFreeSlots() const
			{
				return static_cast<int64_t>(m_Size) - static_cast<int>((m_FreeSlotIndex * 4) >> 2);
			}

			int32_t GetScriptGuid(int32_t Index) const
			{
				return (Index << 8) + m_Flags[Index];
			}

			int32_t GetIndex(int32_t ScriptGuid) const
			{
				return ScriptGuid >> 8;
			}

			bool IsValid(int32_t Index) const
			{
				return !(m_Flags[Index] & 0x80);
			}

			void* GetAt(size_t Index) const
			{
				if (m_Flags[Index])
				{
					if (_fwObj* obj = reinterpret_cast<_fwObj*>(m_Entries + Index * m_ItemSize); obj->m_0010)
						return obj;
				}

				return nullptr;
			}

			// Helper class to check object validity (m_0010)
			class _fwObj
			{
			public:
				virtual ~_fwObj() = 0;
				uint64_t m_0008;
				void* m_0010;
			};

		}; //Size: 0x0030
	#if ENHANCED
		static_assert(sizeof(fwBasePool) == 0x30);
	#else
		static_assert(sizeof(fwBasePool) == 0x28);
	#endif

		class fwVehiclePool
		{
		public:
	#if ENHANCED
			virtual ~fwVehiclePool() = 0;
	#endif
			void** m_PoolAddress;
			std::uint32_t m_Size;
			char _Padding2[36];
			std::uint32_t* m_BitArray;
			char _Padding3[40];
			std::uint32_t m_ItemCount;

			inline bool IsValid(int i) const
			{
				return (m_BitArray[i >> 5] >> (i & 0x1F)) & 1;
			}

			inline void* GetAt(int i) const
			{
				if (IsValid(i))
					return m_PoolAddress[i];

				return nullptr;
			}
		};
	}
}

#endif
