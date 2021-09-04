#include "rtSphere.hpp"
#include <cmath>
#include <algorithm>

namespace rt {
	Sphere::Sphere(rt::Point origin, f32 radius) : Shape() {
		m_origin = origin;
		m_radius = radius;
		m_transform = rt::get_identity_matrix(4);
	}

	std::vector<Intersection> Sphere::intersect(Ray ray) {

		auto inv = rt::inverse(get_transform());
		if(!inv.has_value()) {
			return {};
		}
		rt::Ray r = ray.transform(inv.value());

		rt::Vector sphere_to_ray = (rt::Vector)(r.origin() - m_origin);		
		f32 a = r.direction().dot(r.direction());
		f32 b = 2 * r.direction().dot(sphere_to_ray);
		f32 c = sphere_to_ray.dot(sphere_to_ray) - 1;

		f32 d = pow(b, 2) - 4 * (f64)a * (f64)c;

		// No hit
		if (d < 0) return {};

		// Hit
		auto t1 = (-b - sqrt(d)) / (2 * a);
		auto t2 = (-b + sqrt(d)) / (2 * a);
		return { Intersection(t1, this), Intersection(t2, this) };
	}

	std::optional<Intersection> Sphere::hit(std::vector<Intersection>& xs) {
		std::sort(xs.begin(), xs.end());
		auto lowest = std::lower_bound(xs.begin(), xs.end(), Intersection(0, this));
		if (lowest != xs.end()) {
			return *lowest;
		}
		return std::nullopt;
	}

}