#include "rtWorld.hpp"

#include "rtSphere.hpp"
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

	void World::set_object(const std::shared_ptr<Shape>& shape, bool reset) {
		if (reset) {
			m_objects.clear();
		}
		m_objects.push_back(shape);
	}

	std::vector<Intersection> World::intersect(const Ray& ray) const {

		std::vector<Intersection> xs;

		for (const auto& shape : m_objects) {
			switch (shape->get_type()) {
			case Shape::Type::Sphere: {
				LOG("Sphere!");

				auto sphere = dynamic_cast<Sphere*>(shape.get());
				if (sphere) {
					auto v = sphere->intersect(ray);
					xs.insert(xs.end(), v.begin(), v.end());
				}
				break;
			}
			case Shape::Type::Cube: {
				LOG("Cube!");
				break;
			}
			default: {
				LOG("Unknown!");
				assert(false);
				break;
			}
			}
		}

		std::sort(xs.begin(), xs.end());
		return xs;
	}

	Color World::shade_hit(const Computations& comps) {
		// TODO: support multiple light sources by calling lighting() for each light and adding the colors together
		return lighting(comps.object->get_material(), get_lights()[0], comps.point, comps.eyev, comps.normalv);
	}
	

	void World::create_default() {
		m_lights.push_back(PointLight({ -10,10,10 }, { 1,1,1 }));

		rt::Material m1;
		m1.color({ 0.8f, 1.0f, 0.6f });
		m1.diffuse(0.7f);
		m1.specular(0.2f);

		auto s1 = std::make_shared<Sphere>();
		s1->set_material(m1);

		auto s2 = std::make_shared<Sphere>();
		s2->set_transform(scaling(0.5f, 0.5f, 0.5f));

		m_objects.push_back(s1);
		m_objects.push_back(s2);
	}

	World get_default_world() {
		World w;
		w.create_default();
		return w;

	}

}