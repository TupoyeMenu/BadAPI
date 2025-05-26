
#include "memory/pattern.hpp"

#include "memory/module.hpp"

extern "C" __declspec(dllexport) uint64_t scan_pattern(const char* pattern, const char* module)
{
	if (module == nullptr)
	{
		module = "";
	}
	try
	{
		return ::memory::module(module).scan(::memory::pattern(pattern)).value().as<uint64_t>();
	}
	catch(const std::exception& e)
	{
		LOG(WARNING) << "Failed to find pattern: " << pattern;
		return 0;
	}
}
