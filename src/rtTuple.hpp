#ifndef __RT_TUPLE_HPP__
#define __RT_TUPLE_HPP__

#include "rtDefs.hpp"

namespace rt {
	struct Tuple {
		Tuple() : x(0), y(0), z(0), w(0) {}
		Tuple(f32 _x, f32 _y, f32 _z, f32 _w) {
			x = _x;
			y = _y;
			z = _z;
			w = _w;
		}

		f32 magnitude() const;
		Tuple normalize() const;

		bool is_point() const { return w == 1; }
		bool is_vector() const { return w == 0; }

		f32 x;
		f32 y;
		f32 z;
		f32 w;

		void debug_print() const;
	};

	bool operator==(const Tuple& lhs, const Tuple& rhs);
	Tuple operator+(const Tuple& lhs, const Tuple& rhs);
	Tuple operator-(const Tuple& lhs, const Tuple& rhs);
	Tuple operator-(const Tuple& t);
	Tuple operator*(const Tuple& t, f32 s);
	Tuple operator/(const Tuple& t, f32 s);

	struct Point : public Tuple {
		Point() : Tuple(0, 0, 0, 1) {}
		Point(f32 x, f32 y, f32 z) : Tuple(x, y, z, 1) {}
		Point(const Tuple& t) : Tuple(t.x, t.y, t.z, 1) {}
	};

	struct Vector : public Tuple {
		Vector() : Tuple(0, 0, 0, 0) {}
		Vector(f32 x, f32 y, f32 z) : Tuple(x, y, z, 0) {}
		Vector(const Tuple& t) : Tuple(t.x, t.y, t.z, 0) {}
		Vector normalize() const;
		f32 dot(Vector b) const;
		Vector cross(Vector b) const;
		Vector reflect(Vector normal) const;
	};

	Vector normalize(const Tuple& t);

	struct Color : public Tuple {
		Color() : Tuple(0, 0, 0, 0) {}
		Color(f32 x, f32 y, f32 z) : Tuple(x, y, z, 0) {}
		Color(const Tuple& t) : Tuple(t) {}
		Color& operator=(const Color& c) { 
			x = c.x;
			y = c.y;
			z = c.z;
			return *this; 
		}
		
		f32& r = x;
		f32& g = y;
		f32& b = z;		
	};

	Color operator*(const Color& lhs, const Color& rhs);

	const Color BLACK = Color(0, 0, 0);
	const Color WHITE = Color(1, 1, 1);
}

#endif
