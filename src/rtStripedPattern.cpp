#include "rtStripedPattern.hpp"

#include "rtShape.hpp"
#include "rtMatrix.hpp"

#include <cmath>

namespace rt {
    StripedPattern::StripedPattern(const Color& a, const Color& b)
    {
        m_a = a;
        m_b = b;
        m_transform = get_identity_matrix(4);   
    }

    Color StripedPattern::stripe_at(Point p) const {
        int floor_x = static_cast<i32>(std::floor(p.x));
        if (floor_x % 2 == 0) {
            return m_a;
        }
        else {
            return m_b;
        }
	}

    Color StripedPattern::stripe_at_object(const Shape& shape, const Point& world_point) const {
        Point object_point = rt::inverse(shape.transform()).value() * world_point;
        Point pattern_point = rt::inverse(m_transform).value() * object_point;
        return stripe_at(pattern_point);
    }

    void StripedPattern::set_transform(const Matrix& transform) {
        m_transform = transform;
    }

}