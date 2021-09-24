#ifndef __RT_TRANSFORMATIONS_HPP__
#define __RT_TRANSFORMATIONS_HPP__

#include "rtDefs.hpp"

namespace rt {
	class Matrix;
	struct Point;
	struct Vector;

	Matrix translation(f32 x, f32 y, f32 z);
	Matrix scaling(f32 x, f32 y, f32 z);
	Matrix rotation_x(f32 rot);
	Matrix rotation_y(f32 rot);
	Matrix rotation_z(f32 rot);
	Matrix shearing(f32 xy, f32 xz, f32 yx, f32 yz, f32 zx, f32 zy);
	
	Matrix view_transform(const Point& from, const Point& to, const Vector& up);
}
#endif
