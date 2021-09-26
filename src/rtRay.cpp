#include "rtRay.hpp"
#include "rtMatrix.hpp"
#include "rtLog.hpp"

namespace rt {
	Ray::Ray(Point origin, Vector direction) {
		m_origin = origin;
		m_direction = direction;
	}

	Point Ray::position(f32 t) const {
		return m_origin + m_direction * t;
	}

	Ray Ray::transform(const Matrix& m) const {
		return Ray(m * m_origin, m * m_direction);
	}

	void Ray::debug_print() const {
		LOG("Origin: [%f, %f, %f] - Direction: [%f, %f, %f]", m_origin.x, m_origin.y, m_origin.z, m_direction.x, m_direction.y, m_direction.z);
	}

	bool operator==(const Ray& lhs, const Ray& rhs) {
		if (lhs.origin() == rhs.origin() &&
			lhs.direction() == rhs.direction()) {
			return true;
		}
		return false;
	}
}