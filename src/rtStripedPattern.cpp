#include "rtStripedPattern.hpp"

#include "rtShape.hpp"
#include "rtMatrix.hpp"

#include <cmath>

namespace rt {
    StripedPattern::StripedPattern(const Color& a, const Color& b) : Pattern(Type::STRIPE) {
        m_a = a;
        m_b = b;
    }

    Color StripedPattern::pattern_at(const Point& p) const {
        int floor_x = static_cast<i32>(std::floor(p.x));
        if (floor_x % 2 == 0) {
            return m_a;
        }
        else {
            return m_b;
        }
    }
}