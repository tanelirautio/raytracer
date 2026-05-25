#include "appSphere2.hpp"

#include "rtMain.hpp"

#include <iostream>

namespace app {
	rt::Canvas Sphere2::create(const std::string& image_name, int width, int height) {

		this->width = width;
		this->height = height;

		rt::World w;

		auto& floor = w.emplace_object<rt::Plane>();
		floor.transform() = rt::translation(0, 0.5f, 0);
		floor.transform() = rt::scaling(10, 0.01f, 10);
		floor.material() = rt::Material();
		floor.material().color = rt::Color(0.8f, 0.1f, 0.1f);
		floor.material().specular = 0;
		
		auto& middle = w.emplace_object<rt::Sphere>();
		middle.transform() = rt::translation(-0.5f, 1, 0.5f);
		middle.material() = rt::Material();
		middle.material().color = { 0.1f, 0.2f, 0.5f };
		middle.material().diffuse = 0.7f;
		middle.material().specular = 1.0f;

		
		auto& right = w.emplace_object<rt::Sphere>();
		right.transform() = rt::translation(1.5f, 0.5f, -0.5f) * rt::scaling(0.5f, 0.5f, 0.5f);
		right.material().color = { 0.5f, 1, 0.1f };
		right.material().diffuse = 0.7f;
		right.material().specular = 0.3f;

		auto& left = w.emplace_object<rt::Sphere>();
		left.transform() = rt::translation(-1.5f, 0.33f, -0.75f) * rt::scaling(0.33f, 0.33f, 0.33f);
		left.material() = rt::Material();
		left.material().color = { 1, 0.8f, 0.1f };
		left.material().diffuse = 0.7f;
		left.material().specular = 0.3f;
		

		rt::PointLight light({ -10, 10, -10 }, { 1,1,1 });
		w.set_light(std::make_shared<rt::PointLight>(light));

		rt::Camera camera(width, height, (f32)(M_PI / 3.f));
		camera.transform() = rt::view_transform({ 0, 1.5f, -5 }, { 0,1,0 }, { 0,1,0 });

		auto canvas = camera.render(w);
		std::string name = image_name + ".ppm";
		rt::write_file(name, canvas.canvas_to_ppm());
		
		return canvas;
	}
}
