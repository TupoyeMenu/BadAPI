#include "hooking/detour_hook.hpp"

extern "C" __declspec(dllexport) big::detour_hook* ffi_detour_hook_ctor(const char* name, void* target, void* detour)
{
	return new big::detour_hook(name, target, detour);
}
extern "C" __declspec(dllexport) void ffi_detour_hook_dtor(big::detour_hook* _this)
{
	delete _this;
}
extern "C" __declspec(dllexport) void ffi_detour_hook_enable(big::detour_hook* _this)
{
	_this->enable();
}
extern "C" __declspec(dllexport) void ffi_detour_hook_disable(big::detour_hook* _this)
{
	_this->disable();
}
extern "C" __declspec(dllexport) void* ffi_detour_hook_get_original(big::detour_hook* _this)
{
	return _this->get_original<void*>();
}
