/**
 * @file pattern.cpp
 * 
 * @copyright GNU General Public License Version 2.
 * This file is part of YimMenu.
 * YimMenu is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 2 of the License, or (at your option) any later version.
 * YimMenu is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License along with YimMenu. If not, see <https://www.gnu.org/licenses/>.
 */

#include "pattern.hpp"

#include "common.hpp"

namespace memory
{
	std::optional<uint8_t> to_hex(char const c)
	{
		switch (c)
		{
		case '0': return static_cast<uint8_t>(0x0);
		case '1': return static_cast<uint8_t>(0x1);
		case '2': return static_cast<uint8_t>(0x2);
		case '3': return static_cast<uint8_t>(0x3);
		case '4': return static_cast<uint8_t>(0x4);
		case '5': return static_cast<uint8_t>(0x5);
		case '6': return static_cast<uint8_t>(0x6);
		case '7': return static_cast<uint8_t>(0x7);
		case '8': return static_cast<uint8_t>(0x8);
		case '9': return static_cast<uint8_t>(0x9);
		case 'a': return static_cast<uint8_t>(0xa);
		case 'b': return static_cast<uint8_t>(0xb);
		case 'c': return static_cast<uint8_t>(0xc);
		case 'd': return static_cast<uint8_t>(0xd);
		case 'e': return static_cast<uint8_t>(0xe);
		case 'f': return static_cast<uint8_t>(0xf);
		case 'A': return static_cast<uint8_t>(0xA);
		case 'B': return static_cast<uint8_t>(0xB);
		case 'C': return static_cast<uint8_t>(0xC);
		case 'D': return static_cast<uint8_t>(0xD);
		case 'E': return static_cast<uint8_t>(0xE);
		case 'F': return static_cast<uint8_t>(0xF);
		default: return std::nullopt;
		}
	}

	pattern::pattern(std::string_view ida_sig)
	{
		const auto size_minus_one = ida_sig.size() - 1;
		m_bytes.reserve(size_minus_one / 2);
		for (size_t i = 0; i != size_minus_one; ++i)
		{
			if (ida_sig[i] == ' ')
				continue;

			if (ida_sig[i] != '?')
			{
				auto c1 = to_hex(ida_sig[i]);
				auto c2 = to_hex(ida_sig[i + 1]);
				if (c1 && c2)
				{
					m_bytes.emplace_back(static_cast<uint8_t>((*c1 * 0x10) + *c2));
				}
			}
			else
			{
				m_bytes.push_back({});
			}
		}
	}
}
