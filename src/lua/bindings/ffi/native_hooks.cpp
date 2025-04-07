// Only for ffi, implementing it in any other way is a pain.
// LuaJIT does not even support passing 64bit integers outside of ffi.

#include "native_hooks/native_hooks.hpp"

extern "C" __declspec(dllexport) void ffi_add_native_detour(rage::joaat_t script_hash, uint64_t native_hash, rage::scrNativeHandler detour)
{
	big::g_native_hooks->add_native_detour(script_hash, native_hash, detour);
}

extern "C" __declspec(dllexport) void ffi_hook_program(rage::scrProgram* scr_program)
{
	big::g_native_hooks->hook_program(scr_program);
}
