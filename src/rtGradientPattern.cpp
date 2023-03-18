#include "rtGradientPattern.hpp"

namespace rt {

	GradientPattern::GradientPattern(const Color& a, const Color& b) : Pattern(Type::GRADIENT) {
		m_a = a;
		m_b = b;
	}

	Color GradientPattern::pattern_at(const Point& p) const {
		auto distance = m_b - m_a;
		auto fraction = p.x - std::floor(p.x);
		return m_a + distance * fraction;
	}
}