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
			~Sphere() {}
			
			Point origin() const { return m_origin; }
			f32 radius() const { return m_radius; }

			std::vector<Intersection> intersect(const Ray& r) const override;
			Vector normal_at(const rt::Point& point) const override;
		private:
			Point m_origin;
			f32 m_radius;
	};

	bool operator==(const Sphere& lhs, const Sphere& rhs);
}

#endif