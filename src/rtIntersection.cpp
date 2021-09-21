#include "rtIntersection.hpp"

namespace rt {

	Computations prepare_computations(Intersection i, Ray r) {
		Computations comps;
		comps.t = i.t;
		comps.object = i.object;
		comps.point = r.position(comps.t);
		comps.eyev = -r.direction();
		comps.normalv = i.object->normal_at(comps.point);

		if (comps.normalv.dot(comps.eyev) < 0) {
			comps.inside = true;
			comps.normalv = -comps.normalv;
		}
		else {
			comps.inside = false;
		}

		return comps;
	}
}