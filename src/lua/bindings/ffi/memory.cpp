
#include "gta/pointers.hpp"
#include "memory/module.hpp"
#include "memory/pattern.hpp"

extern "C" __declspec(dllexport) rage::fwEntity* handle_to_ptr(int handle)
{
	return big::g_pointers->m_handle_to_ptr(handle);
}
extern "C" __declspec(dllexport) int ptr_to_handle(rage::fwEntity* ptr)
{
	return big::g_pointers->m_ptr_to_handle(ptr);
}

extern "C" __declspec(dllexport) uint64_t scan_pattern(const char* pattern, const char* module)
{
	if (module == nullptr)
		module = "";

	try
	{
		return ::memory::module(module).scan(::memory::pattern(pattern)).value().as<uint64_t>();
	}
	catch (const std::exception& e)
	{
		LOG(WARNING) << "Failed to find pattern: " << pattern;
		return 0;
	}
}
