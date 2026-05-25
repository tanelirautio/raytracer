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
	
	void World::set_light(const std::shared_ptr<PointLight>& light, bool reset) {
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
		return lighting(comps.object->material(), *comps.object, *get_lights()[0].get(), comps.over_point, comps.eyev, comps.normalv, shadowed);
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
		auto v = m_lights[0].get()->position() - point;
		auto distance = v.magnitude();
		auto direction = v.normalize();

		auto r = Ray(point, direction);
		auto intersections = intersect(r);

		auto h = hit(intersections);
		if (h.has_value() && h.value().t < distance) {
			return true;
		}

		return false;
	}
	
	void World::create_default() {
		auto light = std::make_shared<PointLight>(Point(-10, 10, -10), Vector(1, 1, 1));
		m_lights.push_back(light);

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
