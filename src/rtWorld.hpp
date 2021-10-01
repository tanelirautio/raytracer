#ifndef __RT_WORLD_HPP__
#define __RT_WORLD_HPP__


#include "rtShape.hpp"
#include "rtLight.hpp"

#include <vector>
#include <memory>

namespace rt {
	struct Computations;
	struct Color;
	class Ray;
	class World {
		public:
			World() = default;

			void create_default();

			void set_light(const std::shared_ptr<PointLight>& light, bool reset = false);
			void set_object(const std::shared_ptr<Shape>& shape, bool reset = false);

			std::vector<Intersection> intersect(const Ray& ray) const;
			Color shade_hit(const Computations& comps) const;
			Color color_at(const Ray& ray) const;
			bool is_shadowed(const Point& point) const;

			const std::vector<std::shared_ptr<PointLight>>& get_lights() const { return m_lights; }
			const std::vector<std::shared_ptr<Shape>>& get_objects() const { return m_objects; }
		private:
			std::vector<std::shared_ptr<PointLight>> m_lights;
			std::vector<std::shared_ptr<Shape>> m_objects;
	};

	World get_default_world();
}

#endif