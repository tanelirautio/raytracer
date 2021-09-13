#ifndef __RT_WORLD_HPP__
#define __RT_WORLD_HPP__

#include "rtShape.hpp"
#include "rtLight.hpp"

#include <vector>
#include <memory>

namespace rt {
	class World {
		public:
			World() {};
			void create_default() {}

			std::vector<PointLight> get_lights() { return m_lights; }
			std::vector<Shape> get_objects() { return m_objects; }
		private:
			std::vector<PointLight> m_lights;
			std::vector<Shape> m_objects;
	};

	World get_default_world();
}

#endif