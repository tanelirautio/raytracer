#include "rtShape.hpp"

namespace rt {
	i32 Shape::ID = 0;

	bool operator==(const Shape& lhs, const Shape& rhs) {
		return lhs.id() == rhs.id();
	}
}
