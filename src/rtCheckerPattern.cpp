#include "rtCheckerPattern.hpp"

namespace rt {
	CheckerPattern::CheckerPattern(const Color& a, const Color& b) : Pattern(Type::CHECKER) {
		m_a = a;
		m_b = b;
	}

	Color CheckerPattern::pattern_at(const Point& p) const {
		if ((static_cast<i32>(std::floor(p.x)) + static_cast<i32>(std::floor(p.y)) + static_cast<i32>(std::floor(p.z))) % 2 == 0) {
			return m_a;
		}
		else {
			return m_b;
		}
	}
}