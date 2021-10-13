#include "rtSphere.hpp"
#include <cmath>
#include <algorithm>

namespace rt {
	Sphere::Sphere(Point origin, f32 radius) : Shape(Type::SPHERE) {
		m_origin = origin;
		m_radius = radius;
	}

	std::vector<Intersection> Sphere::local_intersect(const Ray& r) const {
		Vector sphere_to_ray = (Vector)(r.origin() - m_origin);		
		f32 a = r.direction().dot(r.direction());
		f32 b = 2 * r.direction().dot(sphere_to_ray);
		f32 c = sphere_to_ray.dot(sphere_to_ray) - 1;

		f32 d = (f32)(pow(b, 2) - 4 * (d64)a * (d64)c);

		// No hit
		if (d < 0) return {};

		// Hit
		auto t1 = (-b - sqrt(d)) / (2 * a);
		auto t2 = (-b + sqrt(d)) / (2 * a);
		return { Intersection(t1, this), Intersection(t2, this) };
	}

	Vector Sphere::local_normal_at(const Point& local_point) const {
		Vector local_normal = local_point - Point(0, 0, 0);
		return local_normal;

		/*
		Vector world_normal;

		auto transform_inverse = transform().inverse();
		if (transform_inverse.has_value()) {
			auto object_point = transform_inverse.value() * world_point;
			auto object_normal = object_point - Point(0, 0, 0);
			world_normal = transform_inverse.value().transpose() * object_normal;
			world_normal.w = 0;
			return world_normal.normalize();
		}
		return world_normal;
		*/
	}

	bool operator==(const Sphere& lhs, const Sphere& rhs) {
		return lhs.origin() == rhs.origin() &&
			lhs.material() == rhs.material() &&
			lhs.transform() == rhs.transform() &&
			lhs.type() == rhs.type() &&
			equal(lhs.radius(), rhs.radius());
	}
}