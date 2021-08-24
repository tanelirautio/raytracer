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

	Matrix rotation_x(f32 rot) {
		Matrix m = get_identity_matrix(4);
		m.set(1, 1, cos(rot));
		m.set(1, 2, -sin(rot));
		m.set(2, 1, sin(rot));
		m.set(2, 2, cos(rot));
		return m;
	}

	Matrix rotation_y(f32 rot) {
		Matrix m = get_identity_matrix(4);
		m.set(0, 0, cos(rot));
		m.set(0, 2, sin(rot));
		m.set(2, 0, -sin(rot));
		m.set(2, 2, cos(rot));
		return m;
	}

	Matrix rotation_z(f32 rot) {
		Matrix m = get_identity_matrix(4);
		m.set(0, 0, cos(rot));
		m.set(0, 1, -sin(rot));
		m.set(1, 0, sin(rot));
		m.set(1, 1, cos(rot));
		return m;
	}

	Matrix shearing(f32 xy, f32 xz, f32 yx, f32 yz, f32 zx, f32 zy) {
		Matrix m = get_identity_matrix(4);
		m.set(0, 1, xy);
		m.set(0, 2, xz);
		m.set(1, 0, yx);
		m.set(1, 2, yz);
		m.set(2, 0, zx);
		m.set(2, 1, zy);
		return m;
	}

}