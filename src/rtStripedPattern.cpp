#include "rtStripedPattern.hpp"

#include <cmath>

namespace rt {
	Color StripedPattern::stripe_at(Point p) {
        int floor_x = static_cast<i32>(std::floor(p.x));
        if (floor_x % 2 == 0) {
            return a;
        }
        else {
            return b;
        }
	}
}