#include "common.hpp"

extern "C" __declspec(dllexport) bool is_enhanced()
{
	return big::g_is_enhanced;
}