#ifndef __RT_TUPLE_HPP__
#define __RT_TUPLE_HPP__

#include "rtDefs.hpp"

namespace rt {
	class Tuple {
		public:
			Tuple() : m_x(0), m_y(0), m_z(0), m_w(0) {}
			Tuple(f32 x, f32 y, f32 z, f32 w);

			f32 magnitude() const;
			Tuple normalize() const;

			bool is_point() const { return m_w == 1; }
			bool is_vector() const { return m_w == 0; }

			f32 x() const { return m_x; }
			f32 y() const { return m_y; }
			f32 z() const { return m_z; }
			f32 w() const { return m_w; }

			void debug_print();
		private:
			f32 m_x, m_y, m_z, m_w;
	};

	bool operator==(const Tuple& lhs, const Tuple& rhs);
	Tuple operator+(const Tuple& lhs, const Tuple& rhs);
	Tuple operator-(const Tuple& lhs, const Tuple& rhs);
	Tuple operator-(const Tuple& t);
	Tuple operator*(const Tuple& t, f32 s);
	Tuple operator/(const Tuple& t, f32 s);

	class Point : public Tuple {
		public:
			Point() : Tuple(0, 0, 0, 1) {}
			Point(f32 x, f32 y, f32 z) : Tuple(x, y, z, 1) {}
			Point(const Tuple& t) : Tuple(t.x(), t.y(), t.z(), 1) {}
	};

	class Vector : public Tuple {
		public:
			Vector() : Tuple(0, 0, 0, 0) {}
			Vector(f32 x, f32 y, f32 z) : Tuple(x, y, z, 0) {}
			Vector(const Tuple& t) : Tuple(t.x(), t.y(), t.z(), 0) {}
			Vector normalize() const;
			f32 dot(Vector b) const;
			Vector cross(Vector b) const;
	};

	class Color : public Tuple {
		public:
			Color() : Tuple(0, 0, 0, 0) {}
			Color(f32 x, f32 y, f32 z) : Tuple(x, y, z, 0) {}
			Color(const Tuple& t) : Tuple(t) {}
			f32 r() const { return x(); }
			f32 g() const { return y(); }
			f32 b() const { return z(); }
	};

	Color operator*(const Color& lhs, const Color& rhs);

	Color get_color_white();
	Color get_color_black();

}

#endif
