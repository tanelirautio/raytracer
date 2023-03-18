#include "rtPattern.hpp"

#include "rtShape.hpp"
#include "rtTuple.hpp"

namespace rt {

	Color Pattern::pattern_at_shape(const Shape& shape, const Point& p) const {
        Point object_point = rt::inverse(shape.transform()).value() * p;
        Point pattern_point = rt::inverse(m_transform).value() * object_point;
        return pattern_at(pattern_point);
	}

	bool operator==(const Pattern& lhs, const Pattern& rhs) {
		if (lhs.type() == rhs.type() && lhs.transform() == rhs.transform()) {
			return true;
		}
		return false;
	}
}