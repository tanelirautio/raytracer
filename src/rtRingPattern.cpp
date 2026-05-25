#include "rtRingPattern.hpp"

#include <cmath>

namespace rt {
	RingPattern::RingPattern(const Color& a, const Color& b) : Pattern(Type::RING) {
		m_a = a;
		m_b = b;
	}

	Color RingPattern::pattern_at(const Point& p) const {
		auto distance = std::sqrt(p.x * p.x + p.z * p.z);
		if (static_cast<i32>(std::floor(distance)) % 2 == 0) {
			return m_a;
		}
		return m_b;
	}
}