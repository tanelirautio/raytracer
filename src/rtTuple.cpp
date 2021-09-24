#include "rtTuple.hpp"
#include "rtUtil.hpp"
#include "rtLog.hpp"

#include <cmath>
#include <string>

namespace rt {

	bool operator==(const Tuple& lhs, const Tuple& rhs) {
		return equal(lhs.x, rhs.x) &&
			equal(lhs.y, rhs.y) &&
			equal(lhs.z, rhs.z) &&
			equal(lhs.w, rhs.w);
	}

	Tuple operator+(const Tuple& lhs, const Tuple& rhs) {
		return Tuple(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w);
	}

	Tuple operator-(const Tuple& lhs, const Tuple& rhs) {
		return Tuple(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w);
	}

	Tuple operator-(const Tuple& t) {
		return Tuple(-t.x, -t.y, -t.z, -t.w);
	}

	Tuple operator*(const Tuple& t, f32 s) {
		return Tuple(t.x * s, t.y * s, t.z * s, t.w * s);
	}

	Tuple operator/(const Tuple& t, f32 s) {
		return Tuple(t.x / s, t.y / s, t.z / s, t.w / s);
	}

	/*
	Color::Color() : Tuple(0, 0, 0, 0), r(x), g(y), b(z)  {

	}

	Color::Color(f32 x, f32 y, f32 z) : Tuple(x, y, z, 0) {

	}

	Color::Color(const Tuple& t) : Tuple(t) {

	}
	*/

	Color operator*(const Color& lhs, const Color& rhs) {
		return Color(lhs.r * rhs.r, lhs.g * rhs.g, lhs.b * rhs.b);
	}

	Color get_color_white() {
		return Color(1,1,1);
	}

	Color get_color_black() {
		return Color(0,0,0);
	}

	f32 Tuple::magnitude() const {
		return std::sqrt(x * x + y * y + z * z + w * w);
	}

	Tuple Tuple::normalize() const {
		f32 m = magnitude();
		return Tuple(x / m, y / m, z / m, w / m);
	}

	void Tuple::debug_print() {
		LOG("[%f, %f, %f, %f]", x, y, z, w);
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

	Vector Vector::reflect(Vector normal) const {
		return *this - (normal * 2 * dot(normal));
	}

	Vector normalize(const Tuple& t) {
		f32 m = t.magnitude();
		return Tuple(t.x / m, t.y / m, t.z / m, t.w / m);
	}
}