#include "rtWorld.hpp"

#include "rtSphere.hpp"
#include "rtPlane.hpp"
#include "rtTransformations.hpp"
#include "rtIntersection.hpp"
#include "rtTuple.hpp"
#include "rtLog.hpp"

#include <memory>
#include <cassert>

namespace rt {
	
	void World::set_light(const PointLight& light, bool reset) {
		if (reset) {
			m_lights.clear();
		}
		m_lights.push_back(light);
	}

	void World::set_object(std::unique_ptr<Shape> shape, bool reset) {
		if (reset) {
			m_objects.clear();
		}
		m_objects.push_back(std::move(shape));
	}

	std::vector<Intersection> World::intersect(const Ray& ray) const {

		std::vector<Intersection> xs;

		for (const auto& shape : m_objects) {
			auto v = shape->intersect(ray);
			xs.insert(xs.end(), v.begin(), v.end());
		}

		std::sort(xs.begin(), xs.end());
		return xs;
	}

	Color World::shade_hit(const Computations& comps) const {
		auto shadowed = is_shadowed(comps.over_point);
		// TODO: support multiple light sources by calling lighting() for each light and adding the colors together
		Color surface = lighting(comps.object->material(), *comps.object, get_lights()[0], comps.over_point, comps.eyev, comps.normalv, shadowed);

		Color reflected = reflected_color(comps);

		return surface + reflected;
	}

	Color World::color_at(const Ray& ray) const {
		auto xs = intersect(ray);
		if (xs.size() > 0) {
			// Intersections have been already sorted - we just need to find the first intersection with the lowest non-negative value
			for (i32 i = 0; i < xs.size(); i++) {
				if (xs[i].t > 0) {
					return shade_hit(prepare_computations(xs[i], ray));
				}
			}
		}
		return rt::BLACK;
	}

	bool World::is_shadowed(const Point& point) const {
		auto v = m_lights[0].position() - point;
		auto distance = v.magnitude();
		auto direction = v.normalize();

		auto r = Ray(point, direction);
		// Opaque-only shadow check: any positive hit before the light fully blocks it.
		// When transparent materials are introduced, replace this with a light
		// transmittance calculation that accumulates transparency across all blockers.
		return has_opaque_shadow_hit(r, distance);
	}

	bool World::has_opaque_shadow_hit(const Ray& ray, f32 max_distance) const {
		for (const auto& shape : m_objects) {
			auto intersections = shape->intersect(ray);
			for (const auto& intersection : intersections) {
				if (intersection.t > 0 && intersection.t < max_distance) {
					return true;
				}
			}
		}

		return false;
	}

	Color World::reflected_color(const Computations& comps) const {
		if (comps.object->material().reflective == 0) {
			return BLACK;
		}

		Ray reflect_ray(comps.over_point, comps.reflectv);
		Color color = color_at(reflect_ray);

		return color * comps.object->material().reflective;
	}
	
	void World::create_default() {
		m_lights.push_back(PointLight(Point(-10, 10, -10), Vector(1, 1, 1)));

		rt::Material m1;
		m1.color = { 0.8f, 1.0f, 0.6f };
		m1.diffuse = 0.7f;
		m1.specular = 0.2f;

		auto& s1 = emplace_object<Sphere>();
		s1.material() = m1;

		auto& s2 = emplace_object<Sphere>();
		s2.transform() = scaling(0.5f, 0.5f, 0.5f);
	}

	World get_default_world() {
		World w;
		w.create_default();
		return w;

	}

}
