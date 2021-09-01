#ifndef __RT_INTERSECTION_HPP__
#define __RT_INTERSECTION_HPP__

#include "rtUtil.hpp"
#include "rtDefs.hpp"
#include "rtShape.hpp"
#include <vector>
#include <algorithm>

namespace rt {
	struct Intersection {
		Intersection(f32 _t, const Shape* _o) {
			t = _t;
			object = _o;
		}
		f32 t;
		const Shape* object;

		friend bool operator==(const Intersection& lhs, const Intersection& rhs) {
			return equal(lhs.t, rhs.t);
		}
		friend bool operator<(const Intersection& lhs, const Intersection& rhs) {
			return lhs.t < rhs.t;
		}
	};

	template<typename ...Args>
	std::vector<Intersection> intersections(Args const&... args) {
		std::vector<Intersection> xs{ args... };
		std::sort(xs.begin(), xs.end());
		return xs;
	}
}

#endif