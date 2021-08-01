#ifndef __RT_TUPLE_HPP__
#define __RT_TUPLE_HPP__

#include "rtDefs.hpp"

namespace rt {

	//TODO move to math class
	bool equal(f32 a, f32 b); 

	class Tuple {
		public:
			Tuple() : m_x(0), m_y(0), m_z(0), m_w(0) {}
			Tuple(f32 x, f32 y, f32 z, f32 w);

			/*
			Tuple operator+(Tuple t) const;
			Tuple operator-(Tuple t) const;
			Tuple operator-() const;
			Tuple operator*(f32 s) const;
			Tuple operator/(f32 s) const;
			*/

			f32 magnitude() const;
			Tuple normalize() const;

			bool isPoint() const { return m_w == 1; }
			bool isVector() const { return m_w == 0; }

			f32 x() const { return m_x; }
			f32 y() const { return m_y; }
			f32 z() const { return m_z; }
			f32 w() const { return m_w; }

		private:
			f32 m_x, m_y, m_z, m_w;
	};

	bool operator==(const Tuple lhs, const Tuple rhs);
	Tuple operator+(const Tuple lhs, const Tuple rhs);
	Tuple operator-(const Tuple lhs, const Tuple rhs);
	Tuple operator-(const Tuple t);
	Tuple operator*(const Tuple t, f32 s);
	Tuple operator/(const Tuple t, f32 s) ;

	class Point : public Tuple {
		public:
			Point() : Tuple(0, 0, 0, 1) {}
			Point(f32 x, f32 y, f32 z) : Tuple(x, y, z, 1) {}
	};

	class Vector : public Tuple {
		public:
			Vector() : Tuple(0, 0, 0, 0) {}
			Vector(f32 x, f32 y, f32 z) : Tuple(x, y, z, 0) {}
			Vector normalize() const;
			f32 dot(Vector b) const;
			Vector cross(Vector b) const;
	};

	class Color : public Tuple {
		public:
			Color() : Tuple(0, 0, 0, 0) {}
			Color(f32 x, f32 y, f32 z) : Tuple(x, y, z, 0) {}
			f32 r() { return x(); }
			f32 g() { return y(); }
			f32 b() { return z(); }
	};
}

#endif
