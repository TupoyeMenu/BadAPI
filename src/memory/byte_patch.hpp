/**
 * @file byte_patch.hpp
 * 
 * @copyright GNU General Public License Version 2.
 * This file is part of YimMenu.
 * YimMenu is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 2 of the License, or (at your option) any later version.
 * YimMenu is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License along with YimMenu. If not, see <https://www.gnu.org/licenses/>.
 */

#pragma once
#include <span>

namespace memory
{
	template<typename T>
	concept SpanCompatibleType = requires(T a) { std::span{a}; };

	class byte_patch
	{
	public:
		virtual ~byte_patch();

		void apply() const;
		void restore() const;

		void remove() const;

		template<typename TAddr>
		static const std::shared_ptr<byte_patch>& make(TAddr address, std::remove_pointer_t<std::remove_reference_t<TAddr>> value)
		{
			return m_patches.emplace_back(std::shared_ptr<byte_patch>(new byte_patch(address, value)));
		}

		template<typename TAddr, typename T>
		requires SpanCompatibleType<T>
		static const std::shared_ptr<byte_patch>& make(TAddr address, T span_compatible)
		{
			return m_patches.emplace_back(std::shared_ptr<byte_patch>(new byte_patch(address, std::span{span_compatible})));
		}

		static void restore_all();

	private:
		template<typename TAddr>
		byte_patch(TAddr address, std::remove_pointer_t<std::remove_reference_t<TAddr>> value) :
		    m_address(address)
		{
			m_size = sizeof(std::remove_pointer_t<std::remove_reference_t<TAddr>>);

			m_original_bytes = std::make_unique<byte[]>(m_size);
			memcpy(m_original_bytes.get(), m_address, m_size);

			m_value = std::make_unique<byte[]>(m_size);
			memcpy(m_value.get(), &value, m_size);
		}

		template<typename TAddr, typename T, std::size_t N>
		byte_patch(TAddr address, std::span<T, N> span) :
		    m_address((void*)address)
		{
			m_size = span.size();

			m_original_bytes = std::make_unique<byte[]>(m_size);
			memcpy(m_original_bytes.get(), m_address, m_size);

			m_value = std::make_unique<byte[]>(m_size);
			for (int i = 0; i < m_size; i++)
				m_value[i] = span[i];
		}
		static inline std::vector<std::shared_ptr<byte_patch>> m_patches;

	private:
		void* m_address;
		std::unique_ptr<byte[]> m_value;
		std::unique_ptr<byte[]> m_original_bytes;
		std::size_t m_size;

		friend bool operator==(const std::shared_ptr<byte_patch>& a, const byte_patch* b);
	};
}
