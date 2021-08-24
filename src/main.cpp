#define _USE_MATH_DEFINES
#include <cmath>

#include "rtTuple.hpp"
#include "rtFile.hpp"
#include "rtCanvas.hpp"
#include "rtLog.hpp"
#include "rtMatrix.hpp"
#include "rtDefs.hpp"
#include "rtTransformations.hpp"


int main() {

	rt::Point p(0, 1, 0);
	rt::Matrix half_quarter = rt::rotation_x((f32)M_PI / 4.f);
	rt::Matrix full_quarter = rt::rotation_x((f32)M_PI / 2.f);


	rt::Point r = half_quarter * p;
	r.debug_print();

	rt::Point t(0, sqrt(2.f) / 2.f, -sqrt(2.f) / 2.f);
	t.debug_print();
	
	return 0;
}