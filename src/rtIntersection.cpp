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
		return prepare_computations(i, r, std::vector<Intersection>{ i });
	}

	Computations prepare_computations(Intersection i, Ray r, const std::vector<Intersection>& xs) {

		Computations comps;
		std::vector<const Shape*> containers;

		for (const Intersection& current : xs) {
			// "Hit" means the intersection passed to prepare_computations
			const bool is_target = current.object == i.object && equal(current.t, i.t);

			if (is_target) {
				comps.n1 = containers.empty() ? 1.0f : containers.back()->material().refractive_index;
			}

			auto found = std::find(containers.begin(), containers.end(), current.object);

			if (found != containers.end()) {
				// The ray is exiting this object
				containers.erase(found);
			}
			else {
				// The ray is entering this object
				containers.push_back(current.object);
			}

			// State after crossing current.object
			if (is_target) {
				comps.n2 = containers.empty() ? 1.0f : containers.back()->material().refractive_index;
				break;
			}
		}

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

		comps.reflectv = reflect(r.direction(), comps.normalv);

		comps.over_point = comps.point + comps.normalv * EPSILON;

		return comps;
	}
}