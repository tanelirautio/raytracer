#include "rtTransformations.hpp"

#include "rtMatrix.hpp"

namespace rt {

	Matrix translation(f32 x, f32 y, f32 z) {
		rt::Matrix m = get_identity_matrix(4);
		m.set(0, 3, x);
		m.set(1, 3, y);
		m.set(2, 3, z);
		return m;
	}


}