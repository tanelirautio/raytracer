#include "rtIntersection.hpp"

namespace rt {

	std::optional<Intersection> hit(std::vector<Intersection>& xs) {
		xs.erase(std::remove_if(xs.begin(), xs.end(), [](Intersection& i) { return i.t <= 0; }), xs.end());
		std::sort(xs.begin(), xs.end());
		if (xs.size() > 0) {
			return xs[0];
		}
		return std::nullopt;
	}

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