
extern "C" __declspec(dllexport) void ffi_logf_no_level(const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);

	LOGF(eLogLevel::INFO, fmt, args);

	va_end(args);
}
extern "C" __declspec(dllexport) void ffi_logf(eLogLevel log_level, const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);

	LOGF(log_level, fmt, args);

	va_end(args);
}