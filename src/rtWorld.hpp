#ifndef __RT_WORLD_HPP__
#define __RT_WORLD_HPP__

#include "rtShape.hpp"
#include "rtLight.hpp"

#include <vector>
#include <memory>

namespace rt {
	class Ray;
	class World {
		public:
			World() = default;

			void create_default();

			std::vector<Intersection> intersect(const Ray& ray) const;
			
			std::vector<PointLight> get_lights() const { return m_lights; }
			std::vector<std::unique_ptr<Shape>> const& get_objects() const { return m_objects; }

		private:
			std::vector<PointLight> m_lights;
			std::vector<std::unique_ptr<Shape>> m_objects;
	};

	World get_default_world();
}

#endif