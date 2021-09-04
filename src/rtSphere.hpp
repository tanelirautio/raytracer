#ifndef __RT_SPHERE_HPP__
#define __RT_SPHERE_HPP__

#include <optional>
#include "rtDefs.hpp"
#include "rtShape.hpp"
#include "rtTuple.hpp"
#include "rtIntersection.hpp"
#include "rtRay.hpp"
#include "rtMatrix.hpp"

namespace rt {
	class Sphere : public Shape {
		public:
			Sphere(rt::Point origin = rt::Point(0, 0, 0), f32 radius = 1.0f);
			
			rt::Point origin() const { return m_origin; }
			f32 radius() const { return m_radius; }

			Matrix get_transform() const { return m_transform; }
			void set_transform(const rt::Matrix& m) { m_transform = m; }

			std::vector<Intersection> intersect(Ray r);
			std::optional<Intersection> hit(std::vector<Intersection>& intersections);
		private:
			rt::Point m_origin;
			f32 m_radius;
			rt::Matrix m_transform;
	};
}

#endif