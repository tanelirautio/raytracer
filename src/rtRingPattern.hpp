#ifndef __RT_RING_PATTERN_HPP__
#define __RT_RING_PATTERN_HPP__

#include "rtMatrix.hpp"
#include "rtTuple.hpp"
#include "rtPattern.hpp"

namespace rt {
	class Shape;
	class Matrix;
	class RingPattern : public Pattern {
	public:
		RingPattern(const Color& a, const Color& b);
		Color a() const { return m_a; }
		Color b() const { return m_b; }

		Color pattern_at(const Point& p) const final override;
	protected:
		virtual RingPattern* clone_impl() const override { return new RingPattern(*this); };
	private:
		Color m_a;
		Color m_b;

	};
}

#endif