#ifndef __RT_RAY_HPP__
#define __RT_RAY_HPP__

#include "rtTuple.hpp"
#include <vector>

namespace rt {
	class Ray {
		public:
			Ray(Point origin, Vector direction);
			Point position(f32 t) const;

			Point origin() const { return m_origin; }
			Vector direction() const { return m_direction; }
		private:
			Point m_origin;
			Vector m_direction;
	};

	bool operator==(const Ray& lhs, const Ray& rhs);
}

#endif
