#include "rtTuple.hpp"
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

	bool operator==(const Tuple lhs, const Tuple rhs)
	{
		return equal(lhs.x(), rhs.x()) &&
			equal(lhs.y(), rhs.y()) &&
			equal(lhs.z(), rhs.z()) &&
			equal(lhs.w(), rhs.w());
	}

	Tuple operator+(const Tuple lhs, const Tuple rhs) {
		return Tuple(lhs.x() + rhs.x(), lhs.y() + rhs.y(), lhs.z() + rhs.z(), lhs.w() + rhs.w());
	}

	Tuple operator-(const Tuple lhs, const Tuple rhs) {
		return Tuple(lhs.x() - rhs.x(), lhs.y() - rhs.y(), lhs.z() - rhs.z(), lhs.w() - rhs.w());
	}

	Tuple operator-(const Tuple t) {
		return Tuple(-t.x(), -t.y(), -t.z(), -t.w());
	}

	Tuple operator*(const Tuple t, f32 s) {
		return Tuple(t.x() * s, t.y() * s, t.z() * s, t.w() * s);
	}

	Tuple operator/(const Tuple t, f32 s) {
		return Tuple(t.x() / s, t.y() / s, t.z() / s, t.w() / s);
	}

	Tuple::Tuple(f32 x, f32 y, f32 z, f32 w) {
		m_x = x;
		m_y = y;
		m_z = z;
		m_w = w;
	}

	/*
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
	*/

	f32 Tuple::magnitude() const {
		return std::sqrt(m_x * m_x + m_y * m_y + m_z * m_z + m_w * m_w);
	}

	Tuple Tuple::normalize() const {
		f32 m = magnitude();
		return Tuple(m_x / m, m_y / m, m_z / m, m_w / m);
	}

	Vector Vector::normalize() const {
		f32 m = magnitude();
		return Vector(x() / m, y() / m, z() / m);
	}

	f32 Vector::dot(Vector b) const {
		return (x() * b.x() + y() * b.y() + z() * b.z());
	}

	Vector Vector::cross(Vector b) const {
		return Vector(y() * b.z() - z() * b.y(), 
			          z() * b.x() - x() * b.z(),
					  x() * b.y() - y() * b.x());
	}
}