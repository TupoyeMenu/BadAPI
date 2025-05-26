#include "gta/pointers.hpp"

extern "C" __declspec(dllexport) rage::fwEntity* handle_to_ptr(int handle)
{
	return big::g_pointers->m_handle_to_ptr(handle);
}
extern "C" __declspec(dllexport) int ptr_to_handle(rage::fwEntity* ptr)
{
	return big::g_pointers->m_ptr_to_handle(ptr);
}
