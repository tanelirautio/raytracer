#include "rtTuple.hpp"

#include <cmath>

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
		return Tuple(x / s, y / s, z / s, w / s);
	}

	f32 Tuple::magnitude() const {
		return std::sqrt(x * x + y * y + z * z + w * w);
	}

	Tuple Tuple::normalize() const {
		f32 m = magnitude();
		return Tuple(x / m, y / m, z / m, w / m);
	}

	Vector Vector::normalize() const {
		f32 m = magnitude();
		return Vector(x / m, y / m, z / m);
	}

	f32 Vector::dot(Vector b) const {
		return (x * b.x + y * b.y + z * b.z);
	}

	Vector Vector::cross(Vector b) const {
		return Vector(y * b.z - z * b.y, 
			          z * b.x - x * b.z,
					  x * b.y - y * b.x);
	}
}