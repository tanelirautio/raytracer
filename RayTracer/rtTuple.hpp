#ifndef __RT_TUPLE_HPP__
#define __RT_TUPLE_HPP__

#include "rtDefs.hpp"

namespace rt {

	//TODO move to math class
	bool equal(f32 a, f32 b); 

	class Tuple {
		public:
			Tuple() : x(0), y(0), z(0), w(0) {}
			Tuple(f32 x, f32 y, f32 z, f32 w);

			Tuple operator+(Tuple);

			f32 x;
			f32 y;
			f32 z;
			f32 w;

	};

	class Point : public Tuple {
		public:
			Point(f32 x, f32 y, f32 z) : Tuple(x, y, z, 1.0f) {
			}
	};

	class Vector : public Tuple {
		public:
			Vector(f32 x, f32 y, f32 z) : Tuple(x, y, z, 0.0f) {
			}
	};
}

#endif
