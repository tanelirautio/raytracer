#ifndef __RT_SPHERE_HPP__
#define __RT_SPHERE_HPP__

#include <optional>
#include "rtDefs.hpp"
#include "rtShape.hpp"
#include "rtTuple.hpp"
#include "rtIntersection.hpp"
#include "rtRay.hpp"

namespace rt {
	class Sphere : public Shape {
		public:
			Sphere(rt::Point origin = rt::Point(0, 0, 0), f32 radius = 1.0f);
			
			rt::Point origin() { return m_origin; }
			f32 radius() { return m_radius; }

			std::vector<Intersection> intersects(Ray r);
			std::optional<Intersection> hit(std::vector<Intersection>& intersections);
		private:
			rt::Point m_origin;
			f32 m_radius;
	};
}

#endif