#include "gta/script/invoker.hpp"

// TODO: Almost nothing here was tested.

extern "C" __declspec(dllexport) rage::scrNativeHandler get_native_handler(uint64_t hash)
{
	return big::g_native_invoker.get_native_handler(hash);
}

extern "C" __declspec(dllexport) void cache_handlers()
{
	big::g_native_invoker.cache_handlers();
}
extern "C" __declspec(dllexport) bool are_native_handlers_cached()
{
	return big::g_native_invoker.m_handlers_cached;
}

extern "C" __declspec(dllexport) void begin_call()
{
	big::g_native_invoker.begin_call();
}
extern "C" __declspec(dllexport) void end_call(uint64_t hash)
{
	big::g_native_invoker.end_call(hash);
}

extern "C" __declspec(dllexport) void push_arg_int(int arg)
{
	big::g_native_invoker.push_arg(arg);
}
extern "C" __declspec(dllexport) void push_arg_float(float arg)
{
	big::g_native_invoker.push_arg(arg);
}
extern "C" __declspec(dllexport) void push_arg_char(const char* arg)
{
	big::g_native_invoker.push_arg(arg);
}
extern "C" __declspec(dllexport) void push_arg_ptr(void* arg)
{
	big::g_native_invoker.push_arg(arg);
}

extern "C" __declspec(dllexport) int get_return_value_int()
{
	return big::g_native_invoker.get_return_value<int>();
}
extern "C" __declspec(dllexport) float get_return_value_float()
{
	return big::g_native_invoker.get_return_value<float>();
}
extern "C" __declspec(dllexport) const char* get_return_value_char()
{
	return big::g_native_invoker.get_return_value<const char*>();
}
extern "C" __declspec(dllexport) void* get_return_value_ptr()
{
	return big::g_native_invoker.get_return_value<void*>();
}
extern "C" __declspec(dllexport) Vector3* get_return_value_vector3()
{
	return &big::g_native_invoker.get_return_value<Vector3>();
}

extern "C" __declspec(dllexport) void* get_return_address()
{
	return big::g_native_invoker.get_return_address();
}