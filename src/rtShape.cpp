#include "rtShape.hpp"
#include "rtTuple.hpp"
#include "rtIntersection.hpp"
#include <optional>

namespace rt {
	i32 Shape::ID = 0;

	std::vector<Intersection> Shape::intersect(const Ray& ray) const {		
		auto inv = inverse(m_transform);
		if (inv.has_value()) {
			auto local_ray = ray.transform(inv.value());
			return local_intersect(local_ray);		
		}
		return {};
	}

	bool operator==(const Shape& lhs, const Shape& rhs) {
		return lhs.id() == rhs.id();
	}

	//// TESTSHAPE

	Vector TestShape::normal_at(const Point& world_point) const {
		return Vector();
	}

	std::vector<Intersection> TestShape::local_intersect(const Ray& local_ray) const {
		m_saved_ray = local_ray;
		return {};
	}

}
