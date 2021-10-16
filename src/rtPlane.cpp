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
		
		if (abs(r.direction().y) < EPSILON) {
			return {};
		}

		f32 t = -r.origin().y / r.direction().y;
		return{ Intersection(t, this) };
	}

}
