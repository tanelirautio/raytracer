#include "rtWorld.hpp"

#include "rtSphere.hpp"
#include "rtTransformations.hpp"

#include "rtLog.hpp"

#include <memory>
#include <cassert>

namespace rt {

	std::vector<Intersection> World::intersect(const Ray& ray) const {

		std::vector<Intersection> xs;

		/*
		for(auto shape : m_objects) {
			switch (shape.get_type()) {
				case Shape::Sphere: {
					LOG("SPHERE");
					Sphere& sphere = dynamic_cast<Sphere&>(&shape);
					if (sphere) {
						auto v = sphere->intersect(ray);
						xs.insert(xs.end(), v.begin(), v.end());
					}
					break;
				}
				case Shape::Cube: {
					LOG("CUBE");
					//TODO
					break;
				}
				case Shape::Unknown: 
				default: {
					LOG("UNKNOWN OR DEFAULT");
					//assert(false);
					break;
				}
			}
		}
		*/

		return xs;
	}

	void World::create_default() {
		m_lights.push_back(PointLight({ -10,10,10 }, { 1,1,1 }));

		rt::Material m1;
		m1.color({ 0.8f, 1.0f, 0.6f });
		m1.diffuse(0.7f);
		m1.specular(0.2f);
		rt::Sphere s1;
		s1.set_material(m1);

		rt::Matrix t1 = scaling(0.5f, 0.5f, 0.5f);
		rt::Sphere s2;
		s2.set_transform(t1);

		m_objects.push_back(s1);
		m_objects.push_back(s2);
	}

	World get_default_world() {
		World w;
		w.create_default();
		return w;

	}

}