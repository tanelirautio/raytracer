#include "rtShape.hpp"
#include "rtTuple.hpp"
#include "rtIntersection.hpp"
#include <optional>

namespace rt {
	i32 Shape::ID = 0;

	std::vector<Intersection> Shape::intersect(const Ray& ray) const {
		return std::vector<Intersection>(); 
	}

	std::optional<Intersection> Shape::hit(std::vector<Intersection>& intersections) const { 
		return std::nullopt; 
	}

	Vector Shape::normal_at(const Point& world_point) const { 
		return Vector(); 
	}

	bool operator==(const Shape& lhs, const Shape& rhs) {
		return lhs.id() == rhs.id();
	}
}
