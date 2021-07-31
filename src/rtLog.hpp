#ifndef __RT_LOG_HPP__
#define __RT_LOG_HPP__

#include <cstdio>
#include <sstream>

#ifdef _WIN32
	#define NOMINMAX
	#define WIN32_LEAN_AND_MEAN
	#include "windows.h"
#else
	//TODO: OSX & Linux ?
#endif

#define LOG(fmt, ...) output(fmt, ##__VA_ARGS__)

#ifdef _WIN32
	#ifdef _DEBUG
		inline void output(const char* format, ...) {
		char buff[1024];
		va_list arg;
		va_start(arg, format);
		_vsnprintf_s(buff, sizeof(buff), format, arg);
		va_end(arg);

		OutputDebugStringA(buff);
		OutputDebugStringA("\n");
	}
	#else
		inline void output(const char* format, ...) {}
	#endif
#else
	//TODO: OSX & Linux	?
	inline void output(const char* format, ...) {}
#endif


// TODO: create a separate utility class?
template <typename T>
std::string to_string_with_precision(const T a_value, const int n = 6)
{
	std::ostringstream out;
	out.precision(n);
	out << std::fixed << a_value;
	return out.str();
}

#endif 