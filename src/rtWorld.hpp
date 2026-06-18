#ifndef __RT_WORLD_HPP__
#define __RT_WORLD_HPP__


#include "rtShape.hpp"
#include "rtLight.hpp"

#include <vector>
#include <memory>
#include <utility>

namespace rt {
	constexpr int DEFAULT_RECURSIVE_RAY_DEPTH = 5;

	struct Computations;
	struct Color;
	class Ray;
	class World {
		public:
			World() = default;

			void create_default();

			void set_light(const PointLight& light, bool reset = false);
			void set_object(std::unique_ptr<Shape> shape, bool reset = false);
			template <typename T, typename... Args>
			T& emplace_object(Args&&... args) {
				auto object = std::make_unique<T>(std::forward<Args>(args)...);
				T& ref = *object;
				set_object(std::move(object));
				return ref;
			}

			std::vector<Intersection> intersect(const Ray& ray) const;
			Color shade_hit(const Computations& comps, int remaining = DEFAULT_RECURSIVE_RAY_DEPTH) const;
			Color color_at(const Ray& ray, int remaining = DEFAULT_RECURSIVE_RAY_DEPTH) const;
			bool is_shadowed(const Point& point) const;
			Color reflected_color(const Computations& comps, int remaining = DEFAULT_RECURSIVE_RAY_DEPTH) const;

			const std::vector<PointLight>& get_lights() const { return m_lights; }
			const std::vector<std::unique_ptr<Shape>>& get_objects() const { return m_objects; }
		private:
			bool has_opaque_shadow_hit(const Ray& ray, f32 max_distance) const;

			std::vector<PointLight> m_lights;
			std::vector<std::unique_ptr<Shape>> m_objects;
	};

	World get_default_world();
}

#endif
