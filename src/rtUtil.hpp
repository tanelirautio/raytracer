#ifndef __RT_UTIL_HPP__
#define __RT_UTIL_HPP__

#include "rtDefs.hpp"
#include "rtTuple.hpp"
#include <string>
#include <chrono>

namespace rt {
	bool equal(f32 a, f32 b);
	std::string format_duration(std::chrono::milliseconds ms);

	Color lerp_color(const Color& a, const Color& b, f32 t);
	float clamp(f32 x, f32 minval, f32 maxval);
	f32 lerp(f32 a, f32 b, f32 t);
}

#endif