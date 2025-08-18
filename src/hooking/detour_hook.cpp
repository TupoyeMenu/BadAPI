#include "detour_hook.hpp"

#include "common.hpp"
#include "memory/handle.hpp"

#include <MinHook.h>

namespace big
{
	detour_hook::detour_hook(std::string name, void* detour) :
	    m_name(std::move(name)),
	    m_detour(detour)
	{
	}

	detour_hook::detour_hook(std::string name, void* target, void* detour) :
	    m_name(std::move(name)),
	    m_target(target),
	    m_detour(detour)
	{
		create_hook();
	}

	void detour_hook::set_target_and_create_hook(void* target)
	{
		m_target = target;
		create_hook();
	}

	void detour_hook::create_hook()
	{
		if (m_target == nullptr)
		{
			LOGF(FATAL, "Failed to create hook '{}' because it's target is NULL", m_name);
			return;
		}

		fix_hook_address();

		auto status = MH_CreateHook(m_target, m_detour, &m_original);
		if (status != MH_OK)
		{
			LOGF(FATAL, "Failed to create hook '{}' at 0x{:X} (error: {})", m_name, reinterpret_cast<std::uintptr_t>(m_target), MH_StatusToString(status));
			return;
		}

		LOG(INFO) << "Created hook '" << m_name << "'.";
	}

	detour_hook::~detour_hook() noexcept
	{
		if (m_target)
		{
			MH_RemoveHook(m_target);
		}

		LOG(INFO) << "Removed hook '" << m_name << "'.";
	}

	void detour_hook::enable()
	{
		if (auto status = MH_QueueEnableHook(m_target); status != MH_OK)
		LOGF(FATAL, "Failed to enable hook 0x{:X} ({})", uintptr_t(m_target), MH_StatusToString(status));
	}

	void detour_hook::disable()
	{
		if (auto status = MH_QueueDisableHook(m_target); status != MH_OK)
			LOG(WARNING) << "Failed to disable hook '" << m_name << "'.";
	}

	void detour_hook::fix_hook_address()
	{
		auto ptr = memory::handle(m_target);
		while (ptr.as<std::uint8_t&>() == 0xE9)
			ptr = ptr.add(1).rip();
		m_target = ptr.as<void*>();
	}
}
