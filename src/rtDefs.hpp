#ifndef __RT_DEFS_HPP__
#define __RT_DEFS_HPP__

#include <cstdint>

// ignore warning "conversion from <sometype> to <othertype>: possible loss of data"
#pragma warning( disable : 4244 ) 

// ignore warning "fopen might be unsafe"
#pragma warning( disable : 4996 )

namespace rt {

	typedef int8_t		i8;
	typedef int16_t		i16;
	typedef int32_t		i32;
	typedef int64_t		i64;

	typedef uint8_t		u8;
	typedef uint16_t	u16;
	typedef uint32_t	u32;
	typedef uint64_t	u64;

	typedef float		f32;
	typedef double		f64;

	const f32 EPSILON = 0.00001f;
}

#endif