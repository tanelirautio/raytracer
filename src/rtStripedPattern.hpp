#ifndef __RT_STRIPED_PATTERN_HPP__
#define __RT_STRIPED_PATTERN_HPP__

#include "rtTuple.hpp"

namespace rt {
	class StripedPattern {
		public:
			StripedPattern(const Color& _a, const Color& _b) {
				a = _a;
				b = _b;
			}
			Color stripe_at(Point p);
			Color a;
			Color b;
		private:

	};
}

#endif