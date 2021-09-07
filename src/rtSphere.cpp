#include "rtSphere.hpp"
#include <cmath>
#include <algorithm>

namespace rt {
	Sphere::Sphere(rt::Point origin, f32 radius) : Shape() {
		m_origin = origin;
		m_radius = radius;
		m_transform = rt::get_identity_matrix(4);
	}

	std::vector<Intersection> Sphere::intersect(Ray ray) const {

		auto inv = rt::inverse(get_transform());
		if(!inv.has_value()) {
			return {};
		}
		rt::Ray r = ray.transform(inv.value());

		rt::Vector sphere_to_ray = (rt::Vector)(r.origin() - m_origin);		
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

	rt::Vector Sphere::normal_at(const rt::Point& world_point) const {
		rt::Vector world_normal;

		auto transform_inverse = get_transform().inverse();
		if (transform_inverse.has_value()) {
			auto object_point = transform_inverse.value() * world_point;
			auto object_normal = object_point - rt::Point(0, 0, 0);
			world_normal = transform_inverse.value().transpose() * object_normal;
			world_normal.w(0);
			return world_normal.normalize();
		}
		return world_normal;
	}

}