#pragma once
#include "rage/joaat.hpp"

#include <cstddef>
#include <cstdint>
#include <string_view>
#include <type_traits>

namespace rage
{
	template<size_t N>
	inline constexpr joaat_t consteval_joaat(char const (&data)[N])
	{
		joaat_t hash = 0;

		for (std::size_t i = 0; i < N - 1; ++i)
		{
			hash += joaat_to_lower(data[i]);
			hash += (hash << 10);
			hash ^= (hash >> 6);
		}

		hash += (hash << 3);
		hash ^= (hash >> 11);
		hash += (hash << 15);

		return hash;
	}

	inline consteval joaat_t consteval_joaat(const std::span<const char>& data)
	{
		joaat_t hash = 0;

		for (std::size_t i = 0; i < data.size() - 1; ++i)
		{
			hash += joaat_to_lower(data[i]);
			hash += (hash << 10);
			hash ^= (hash >> 6);
		}

		hash += (hash << 3);
		hash ^= (hash >> 11);
		hash += (hash << 15);

		return hash;
	}
	static_assert(consteval_joaat("test") == 0x3f75ccc1);

	inline constexpr joaat_t literal_joaat(const std::string_view str)
	{
		joaat_t hash = 0;
		for (auto c : str)
		{
			hash += c;
			hash += (hash << 10);
			hash ^= (hash >> 6);
		}
		hash += (hash << 3);
		hash ^= (hash >> 11);
		hash += (hash << 15);
		return hash;
	}
}

inline consteval char consteval_to_lower(char c)
{
	return c >= 'A' && c <= 'Z' ? c | 1 << 5 : c;
}

inline consteval rage::joaat_t operator""_J(const char* s, std::size_t n)
{
	rage::joaat_t result = 0;

	for (std::size_t i = 0; i < n; i++)
	{
		result += consteval_to_lower(s[i]);
		result += (result << 10);
		result ^= (result >> 6);
	}

	result += (result << 3);
	result ^= (result >> 11);
	result += (result << 15);

	return result;
}
static_assert("test"_J == 0x3f75ccc1);

#define RAGE_JOAAT_IMPL(str) (::rage::consteval_joaat(str))
#define RAGE_JOAAT(str) (std::integral_constant<rage::joaat_t, RAGE_JOAAT_IMPL(str)>::value)