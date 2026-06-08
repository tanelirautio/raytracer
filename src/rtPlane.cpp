#include "rtPlane.hpp"

#include "rtDefs.hpp"
#include "rtTuple.hpp"
#include "rtRay.hpp"
#include "rtIntersection.hpp"
#include <cmath>

namespace rt {

	Vector Plane::local_normal_at(const Point& p) const {
		return Vector(0,1,0);
	}

	std::vector<Intersection> Plane::local_intersect(const Ray& r) const {
		
		const f32 dy = r.direction().y;

		if (std::abs(dy) < EPSILON) {
			return {};
		}

		f32 t = -r.origin().y / dy;
		return{ Intersection(t, this) };
	}

}
