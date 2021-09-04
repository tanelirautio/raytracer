#include "appSphere.hpp"

#include "rtTuple.hpp"
#include "rtRay.hpp"
#include "rtCanvas.hpp"
#include "rtSphere.hpp"
#include "rtDefs.hpp"
#include "rtFile.hpp"

#include <iostream>

namespace app {
	void Sphere::create() {

		auto ray_origin = rt::Point(0, 0, -5);
		auto wall_z = 10.f;
		auto wall_size = 7.f;
		auto canvas_pixels = 100.f;
		auto pixel_size = wall_size / canvas_pixels;
		auto half = wall_size / 2;

		auto canvas = rt::Canvas(canvas_pixels, canvas_pixels);
		auto color = rt::Color(1, 0, 0); //red
		auto color2 = rt::Color(0, 0, 1); // blue
		auto shape = rt::Sphere();

		for (i32 y = 0; y < canvas_pixels; y++) {
			auto world_y = half - pixel_size * y;
			for (i32 x = 0; x < canvas_pixels; x++) {
				auto world_x = -half + pixel_size * x;
				auto position = rt::Point(world_x, world_y, wall_z);

				auto dir(position - ray_origin);

				auto r = rt::Ray(ray_origin, dir.normalize());
				auto xs = shape.intersect(r);
				auto hit = shape.hit(xs);
				if (hit.has_value()) {
					canvas.write_pixel(x, y, color);
				}				
			}
		}

		rt::File::write("sphere.ppm", canvas.canvas_to_ppm());

	}
}