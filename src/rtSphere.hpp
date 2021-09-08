#ifndef __RT_SPHERE_HPP__
#define __RT_SPHERE_HPP__

#include <optional>
#include "rtDefs.hpp"
#include "rtShape.hpp"
#include "rtTuple.hpp"
#include "rtIntersection.hpp"
#include "rtRay.hpp"
#include "rtMatrix.hpp"
#include "rtMaterial.hpp"

namespace rt {
	class Sphere : public Shape {
		public:
			Sphere(Point origin = Point(0, 0, 0), f32 radius = 1.0f);
			
			Point origin() const { return m_origin; }
			f32 radius() const { return m_radius; }

			Matrix get_transform() const { return m_transform; }
			void set_transform(const Matrix& m) { m_transform = m; }

			Material get_material() { return m_material; }
			void set_material(const Material& m) { m_material = m; }

			std::vector<Intersection> intersect(Ray r) const;
			std::optional<Intersection> hit(std::vector<Intersection>& intersections) const;
			Vector normal_at(const rt::Point& point) const;
		private:
			Point m_origin;
			f32 m_radius;
			Matrix m_transform;
			Material m_material;
	};
}

#endif