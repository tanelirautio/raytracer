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
	Color operator*(const Color& color, f32 scalar);

	const Color BLACK = Color(0, 0, 0);
	const Color WHITE = Color(1, 1, 1);
	const Color RED = Color(1, 0, 0);
	const Color LIME_GREEN = Color(0, 1, 0);
	const Color BLUE = Color(0, 0, 1);
	const Color CYAN = Color(0, 1, 1);
	const Color YELLOW = Color(1, 1, 0);
	const Color MAGENTA = Color(1, 0, 1);
	const Color GRAY = Color(0.5f, 0.5f, 0.5f);
	const Color ORANGE = Color(1, 0.4f, 0);
	const Color GREEN = Color(0, 0.5f, 0);
	const Color PURPLE = Color(0.5f, 0, 0.5f);
	const Color NAVY_BLUE = Color(0, 0, 0.5f);
	const Color OLIVE = Color(0.5f, 0.5f, 0);

	const Color SILVER = Color(192.f / 255.f, 192.f / 255.f, 192.f / 255.f);
	const Color SKY_BLUE = Color(135.f / 255.f, 206.f / 255.f, 235.f / 255.f);
	const Color LIGHT_BLUE = Color(173.f / 255.f, 216.f / 255.f, 230.f / 255.f);
	const Color HOT_PINK = Color(1, 105.f / 255.f, 180.f / 255.f);
	const Color DEEP_PINK = Color(1, 20.f / 255.f, 147.f / 255.f);
	const Color DARK_GREEN = Color(0, 100.f / 255.f, 0);
	const Color ORANGE_RED = Color(1, 69.f / 255.f, 0);


}

#endif
