#ifndef __RT_TRANSFORMATIONS_HPP__
#define __RT_TRANSFORMATIONS_HPP__

#include "rtDefs.hpp"

namespace rt {
	class Matrix;

	Matrix translation(f32 x, f32 y, f32 z);
	Matrix scaling(f32 x, f32 y, f32 z);
	Matrix rotateX(f32 rot);
	Matrix rotateY(f32 rot);
	Matrix rotateZ(f32 rot);
}
#endif
