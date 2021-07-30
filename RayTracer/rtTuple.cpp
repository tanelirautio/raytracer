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

	Tuple Tuple::operator+(Tuple t) const {
		return Tuple(x + t.x, y + t.y, z + t.z, w + t.w);
	}	
	
	Tuple Tuple::operator-(Tuple t) const {
		return Tuple(x - t.x, y - t.y, z - t.z, w - t.w);
	}

	Tuple Tuple::operator-() const {
		return Tuple(-this->x, -this->y, -this->z, -this->w);
	}

	Tuple Tuple::operator*(f32 s) const {
		return Tuple(x * s, y * s, z * s, w * s);
	}

	Tuple Tuple::operator/(f32 s) const {
		return Tuple(x/s, y/s, z/s, w/s);
	}
}