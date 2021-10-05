#ifndef __RT_UTIL_HPP__
#define __RT_UTIL_HPP__

#include "rtDefs.hpp"
#include <string>
#include <chrono>

namespace rt {
	bool equal(f32 a, f32 b);
	std::string format_duration(std::chrono::milliseconds ms);
}

#endif