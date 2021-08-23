#include "rtTransformations.hpp"

#include "rtMatrix.hpp"

#include <cmath>

namespace rt {

	Matrix translation(f32 x, f32 y, f32 z) {
		rt::Matrix m = get_identity_matrix(4);
		m.set(0, 3, x);
		m.set(1, 3, y);
		m.set(2, 3, z);
		return m;
	}

	Matrix scaling(f32 x, f32 y, f32 z) {
		rt::Matrix m = get_identity_matrix(4);
		m.set(0, 0, x);
		m.set(1, 1, y);
		m.set(2, 2, z);
		return m;
	}

	Matrix rotateX(f32 rot) {
		Matrix m = get_identity_matrix(4);
		m.set(1, 1, cos(rot));
		m.set(1, 2, -sin(rot));
		m.set(2, 1, sin(rot));
		m.set(2, 2, cos(rot));
		return m;
	}

	Matrix rotateY(f32 rot) {
		Matrix m = get_identity_matrix(4);
		m.set(0, 0, cos(rot));
		m.set(0, 2, sin(rot));
		m.set(2, 0, -sin(rot));
		m.set(2, 2, cos(rot));
		return m;
	}

	Matrix rotateZ(f32 rot) {
		Matrix m = get_identity_matrix(4);
		m.set(0, 0, cos(rot));
		m.set(0, 1, -sin(rot));
		m.set(1, 0, sin(rot));
		m.set(1, 1, cos(rot));
		return m;
	}

}