#include "rtTuple.hpp"

namespace rt {

	//TODO: move to math class
	bool equal(f32 a, f32 b)
	{
		if (std::abs(a - b) < EPSILON) {
			return true;
		}
		return false;
	}

	Tuple::Tuple(f32 x, f32 y, f32 z, f32 w) {
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	Tuple Tuple::operator+(Tuple t) {
		Tuple r;
		r.x = this->x + t.x;
		r.y = this->y + t.y;
		r.z = this->z + t.z;
		r.w = this->w + t.w;
		return r;
	}
}