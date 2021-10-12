#ifndef __RT_RAY_HPP__
#define __RT_RAY_HPP__

#include "rtTuple.hpp"
#include <vector>

namespace rt {
	class Matrix;
	class Ray {
		public:
			Ray() : Ray({ 0,0,0 }, { 0,0,1 }) {}
			Ray(Point origin, Vector direction);
			Point position(f32 t) const;

			const Point& origin() const { return m_origin; }
			Point& origin() { return m_origin; }

			const Vector& direction() const { return m_direction; }
			Vector& direction() { return m_direction; }

			Ray transform(const Matrix& m) const;

			void debug_print() const;
		private:
			Point m_origin;
			Vector m_direction;
	};

	bool operator==(const Ray& lhs, const Ray& rhs);
}

#endif
