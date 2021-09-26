#ifndef __RT_DEFS_HPP__
#define __RT_DEFS_HPP__

#include <cstdint>

// ignore warning "conversion from <sometype> to <othertype>: possible loss of data"
//#pragma warning( disable : 4244 ) 

// ignore warning "fopen might be unsafe"
//#pragma warning( disable : 4996 )


typedef int8_t		i8;
typedef int16_t		i16;
typedef int32_t		i32;
typedef int64_t		i64;

typedef uint8_t		u8;
typedef uint16_t	u16;
typedef uint32_t	u32;
typedef uint64_t	u64;

typedef float		f32;
typedef double		d64;

constexpr f32 EPSILON = 0.00001f;

#define _USE_MATH_DEFINES
#include <cmath>

#ifndef M_PI
constexpr f32 M_PI = 3.14159265358979323846f;
#endif

constexpr f32 HALF_PI = (f32)M_PI / 2.f;

#endif