#include "appSphere.hpp"

#include "rtTuple.hpp"
#include "rtRay.hpp"
#include "rtCanvas.hpp"
#include "rtSphere.hpp"
#include "rtDefs.hpp"
#include "rtFile.hpp"
#include "rtLight.hpp"
#include "rtTransformations.hpp"

#include <iostream>

namespace app {
	void Sphere::create() {

		auto ray_origin = rt::Point(0, 0, -5);
		auto wall_z = 10.f;
		auto wall_size = 7.f;
		auto canvas_pixels = 100.f;
		auto pixel_size = wall_size / canvas_pixels;
		auto half = wall_size / 2;

		auto canvas = rt::Canvas((i32)canvas_pixels, (i32)canvas_pixels);
		
		auto shape = rt::Sphere();
		shape.material().color = { 1, 0.2f, 1 };
		
		//shape.transform() = rt::rotation_z((f32)M_PI/4.f) * rt::scaling(0.5f, 1, 1);

		auto light_position = rt::Point(-10, 10, -10);
		auto light_color = rt::Color(1, 1, 1);
		auto light = rt::PointLight(light_position, light_color);

		for (i32 y = 0; y < canvas_pixels; y++) {
			auto world_y = half - pixel_size * y;
			for (i32 x = 0; x < canvas_pixels; x++) {
				auto world_x = -half + pixel_size * x;
				auto position = rt::Point(world_x, world_y, wall_z);

				auto dir = (position - ray_origin).normalize();

				auto ray = rt::Ray(ray_origin, dir);
				auto xs = shape.intersect(ray);
				auto hit = rt::hit(xs);
				if (hit.has_value()) {
					auto point = ray.position(hit.value().t);
					auto normal = shape.normal_at(point);
					auto eye = -ray.direction();
					auto color = rt::lighting(hit.value().object->material(), *hit.value().object, light, point, eye, normal);
					canvas.write_pixel(x, y, color);
				}				
			}
		}

		rt::write_file("sphere2.ppm", canvas.canvas_to_ppm());

	}
}