#include "rtSphere.hpp"
#include <cmath>
#include <algorithm>

namespace rt {
	Sphere::Sphere(Point origin, f32 radius) : Shape(Type::Sphere) {
		m_origin = origin;
		m_radius = radius;
		m_transform = get_identity_matrix(4);
	}

	std::vector<Intersection> Sphere::intersect(const Ray& ray) const {

		auto inv = inverse(transform());
		if(!inv.has_value()) {
			return {};
		}
		Ray r = ray.transform(inv.value());

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

	std::optional<Intersection> Sphere::hit(std::vector<Intersection>& xs) const {
		std::sort(xs.begin(), xs.end());
		auto lowest = std::lower_bound(xs.begin(), xs.end(), Intersection(0, this));
		if (lowest != xs.end()) {
			return *lowest;
		}
		return std::nullopt;
	}

	Vector Sphere::normal_at(const Point& world_point) const {
		Vector world_normal;

		auto transform_inverse = transform().inverse();
		if (transform_inverse.has_value()) {
			auto object_point = transform_inverse.value() * world_point;
			auto object_normal = object_point - Point(0, 0, 0);
			world_normal = transform_inverse.value().transpose() * object_normal;
			world_normal.w(0);
			return world_normal.normalize();
		}
		return world_normal;
	}

	bool operator==(const Sphere& lhs, const Sphere& rhs) {
		return lhs.origin() == rhs.origin() &&
			lhs.material() == rhs.material() &&
			lhs.transform() == rhs.transform() &&
			lhs.type() == rhs.type() &&
			equal(lhs.radius(), rhs.radius());
	}
}