#ifndef __RT_STRIPED_PATTERN_HPP__
#define __RT_STRIPED_PATTERN_HPP__

#include "rtMatrix.hpp"
#include "rtTuple.hpp"
#include "rtPattern.hpp"

namespace rt {
	class Shape;
	class Matrix;
	class StripedPattern : public Pattern {
		public:
			StripedPattern(const Color& a, const Color& b);
			Color a() const { return m_a; }
			Color b() const { return m_b; }

			Color pattern_at(const Point& p) const final override;
		private:
			Color m_a;
			Color m_b;

	};
}

#endif