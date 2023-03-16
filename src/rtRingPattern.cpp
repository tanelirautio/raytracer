#include "rtRingPattern.hpp"

#include <cmath>

namespace rt {
	RingPattern::RingPattern(const Color& a, const Color& b) : Pattern(Type::RING) {
		m_a = a;
		m_b = b;
	}

	Color RingPattern::pattern_at(const Point& p) const {
		if (static_cast<i32>(std::floor(std::sqrt(std::pow(p.x, 2) + std::pow(p.z, 2)) + 0.5)) % 2 == 0) {
			return m_a;
		}
		else {
			return m_b;
		}
	}
}