#include "appClock.hpp"

#define _USE_MATH_DEFINES // M_PI
#include <cmath>

#include "rtTuple.hpp"
#include "rtFile.hpp"
#include "rtCanvas.hpp"
#include "rtLog.hpp"
#include "rtMatrix.hpp"
#include "rtDefs.hpp"
#include "rtTransformations.hpp"

namespace app {
	void Clock::create() {
		std::vector<rt::Point> points;
		points.push_back(rt::Point(0, 0, 1));

		for (i32 i = 1; i < 12; i++) {
			rt::Point p = rt::rotation_y(i * (f32)M_PI / 6) * rt::Point(0, 0, 1);
			p.debug_print();
			points.push_back(p);
		}

		rt::Canvas canvas(800, 800);
		auto radius = (3.f / 8.f) * canvas.get_width();

		for (auto& p : points) {
			auto x = p.x() * radius + 400;
			auto y = p.z() * radius + 400;
			LOG("x: %f y: %f", x, y);
			canvas.write_pixel(x, y, rt::get_color_white());
		}

		rt::File::write("clock.ppm", canvas.canvas_to_ppm());
	}

}