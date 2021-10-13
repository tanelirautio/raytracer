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

	Vector Shape::normal_at(const Point& point) const {
		Vector world_normal;

		auto inv_transform = inverse(m_transform);
		if(inv_transform.has_value()) {
			auto local_point = inv_transform.value() * point;
			auto local_normal = local_normal_at(local_point);
			world_normal = inv_transform.value().transpose() * local_normal;
			world_normal.w = 0;
			return world_normal.normalize();
		}
		return world_normal;
	}

	bool operator==(const Shape& lhs, const Shape& rhs) {
		return lhs.id() == rhs.id();
	}

	//// TESTSHAPE

	Vector TestShape::local_normal_at(const Point& local_point) const {
		return Vector(local_point.x, local_point.y, local_point.z);
	}

	std::vector<Intersection> TestShape::local_intersect(const Ray& local_ray) const {
		m_saved_ray = local_ray;
		return {};
	}

}
