#ifndef __RT_STRIPED_PATTERN_HPP__
#define __RT_STRIPED_PATTERN_HPP__

#include "rtMatrix.hpp"
#include "rtTuple.hpp"

namespace rt {
	class Shape;
	class Matrix;
	class StripedPattern {
		public:
			StripedPattern(const Color& a, const Color& b);
			Color stripe_at(Point p) const;
			Color stripe_at_object(const Shape& shape, const Point& world_point) const;
			void set_transform(const Matrix& transform);
			Color a() const { return m_a; }
			Color b() const { return m_b; }
		private:
			Color m_a;
			Color m_b;
			Matrix m_transform;
	};
}

#endif