#include "appSphere2.hpp"

#include "rtMain.hpp"

#include <iostream>

namespace app {
	void Sphere2::create() {

		auto floor = rt::Sphere();
		floor.transform() = rt::scaling(10, 0.01f, 10);
		floor.material() = rt::Material();
		floor.material().color = rt::Color(1, 0.9f, 0.9f);
		floor.material().specular = 0;

		auto left_wall = rt::Sphere();
		left_wall.transform() = rt::translation(0, 0, 5) * rt::rotation_y(-M_PI / 4.f) * rt::rotation_x(HALF_PI) * rt::scaling(10, 0.01, 10);
		left_wall.material() = floor.material();		
		
		auto right_wall = rt::Sphere();
		right_wall.transform() = rt::translation(0, 0, 5) * rt::rotation_y(M_PI / 4.f) * rt::rotation_x(HALF_PI) * rt::scaling(10, 0.01, 10);
		right_wall.material() = floor.material();

		auto middle = rt::Sphere();
		middle.transform() = rt::translation(-0.5f, 1, 0.5f);
		middle.material() = rt::Material();
		//middle.material().color = rt::Color(0.1f, 1, 0.5f);
		middle.material().color = { 0.1f, 1, 0.5f };
		middle.material().diffuse = 0.7f;
		middle.material().specular = 0.3f;

		auto right = rt::Sphere();
		right.transform() = rt::translation(1.5f, 0.5f, -0.5f) * rt::scaling(0.5f, 0.5f, 0.5f);
		right.material().color = { 0.5f, 1, 0.1f };
		right.material().diffuse = 0.7f;
		right.material().specular = 0.3f;

		auto left = rt::Sphere();
		left.transform() = rt::translation(-1.5f, 0.33f, -0.75f) * rt::scaling(0.33f, 0.33f, 0.33f);
		left.material() = rt::Material();
		left.material().color = { 1, 0.8f, 0.1f };
		left.material().diffuse = 0.7f;
		left.material().specular = 0.3f;

		rt::World w;
		w.set_object(std::make_shared<rt::Sphere>(floor));
		w.set_object(std::make_shared<rt::Sphere>(left_wall));
		w.set_object(std::make_shared<rt::Sphere>(right_wall));
		w.set_object(std::make_shared<rt::Sphere>(middle));
		w.set_object(std::make_shared<rt::Sphere>(right));
		w.set_object(std::make_shared<rt::Sphere>(left));

		rt::PointLight light({ -10, 10, -10 }, { 1,1,1 });
		w.set_light(std::make_shared<rt::PointLight>(light));

		rt::Camera camera(100, 50, M_PI / 3.f);
		camera.transform() = rt::view_transform({ 0, 1.5f, -5 }, { 0,1,0 }, { 0,1,0 });

		auto canvas = camera.render(w);
		rt::write_file("spheres.ppm", canvas.canvas_to_ppm());
		
	}
}