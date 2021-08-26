#include "rtRay.hpp"

namespace rt {
	Ray::Ray(Point origin, Vector direction) {
		m_origin = origin;
		m_direction = direction;
	}

	Point Ray::position(f32 t) const {
		return m_origin + m_direction * t;
	}

	bool operator==(const Ray& lhs, const Ray& rhs) {
		if (lhs.origin() == rhs.origin() &&
			lhs.direction() == rhs.direction()) {
			return true;
		}
		return false;
	}
}