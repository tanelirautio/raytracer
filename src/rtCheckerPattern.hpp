#ifndef __RT_CHECKER_PATTERN__
#define __RT_CHECKER_PATTERN__

#include "rtMatrix.hpp"
#include "rtTuple.hpp"
#include "rtPattern.hpp"

namespace rt {
	class Shape;
	class Matrix;
	class CheckerPattern : public Pattern {
	public:
		CheckerPattern(const Color& a, const Color& b);
		Color a() const { return m_a; }
		Color b() const { return m_b; }

		Color pattern_at(const Point& p) const final override;
	private:
		Color m_a;
		Color m_b;

	};
}

#endif