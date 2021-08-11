#include "rtUtil.hpp"

#include "rtDefs.hpp"
#include <cmath>

namespace rt {

	//TODO: move to math class
	bool equal(f32 a, f32 b) {
		if (std::abs(a - b) < EPSILON) {
			return true;
		}
		return false;
	}

}