#include "appSphere3.hpp"
#include "rtCamera.hpp"
#include "rtMain.hpp"

#include <iostream>

namespace app {
	Sphere3::Sphere3(i32 width, i32 height)
	{
		m_width = width;
		m_height = height;
		m_camera = rt::make_camera(width, height, (f32)(M_PI / 3.f));
	}

	rt::Canvas Sphere3::create() {

		auto floor = rt::Plane();
		floor.transform() = rt::translation(0, 0.5f, 0);
		floor.transform() = rt::scaling(10, 0.01f, 10);
		floor.material() = rt::Material();
		floor.material().color = rt::Color(0.8f, 0.1f, 0.1f);
		floor.material().specular = 0;
		floor.material().pattern = std::make_shared<rt::CheckerPattern>(rt::NAVY_BLUE, rt::SKY_BLUE);
		floor.material().pattern.get()->transform() = rt::scaling(0.02f, 0.02f, 0.02f);

		auto middle = rt::Sphere();
		middle.transform() = rt::translation(-0.5f, 1, 0.5f);
		middle.material() = rt::Material();
		middle.material().color = { 0.1f, 0.2f, 0.5f };
		middle.material().diffuse = 0.7f;
		middle.material().specular = 1.0f;
		middle.material().pattern = std::make_shared<rt::RingPattern>(rt::OLIVE, rt::DARK_GREEN);
		middle.material().pattern.get()->transform() = rt::scaling(0.1f, 0.1f, 0.1f) * rt::rotation_x((f32)M_PI/2.f);

		auto right = rt::Sphere();
		right.transform() = rt::translation(1.5f, 0.5f, -0.5f) * rt::scaling(0.5f, 0.5f, 0.5f);
		right.material().color = { 0.5f, 1, 0.1f };
		right.material().diffuse = 0.7f;
		right.material().specular = 0.3f;
		right.material().pattern = std::make_shared<rt::PerlinPattern>(rt::SILVER, rt::DEEP_PINK);
		right.material().pattern.get()->transform() = rt::scaling(0.25f, 0.25f, 0.25f);

		auto left = rt::Sphere();
		left.transform() = rt::translation(-1.5f, 0.33f, -0.75f) * rt::scaling(0.33f, 0.33f, 0.33f);
		left.material() = rt::Material();
		left.material().color = { 1, 0.8f, 0.1f };
		left.material().diffuse = 0.7f;
		left.material().specular = 0.3f;
		left.material().pattern = std::make_shared<rt::RingPattern>(rt::WHITE, rt::HOT_PINK);
		left.material().pattern.get()->transform() = rt::scaling(0.1f, 0.1f, 0.1f) * rt::rotation_x((f32)M_PI / 2.f);

		rt::World w;
		w.set_object(std::make_shared<rt::Plane>(floor));
		w.set_object(std::make_shared<rt::Sphere>(middle));
		w.set_object(std::make_shared<rt::Sphere>(right));
		w.set_object(std::make_shared<rt::Sphere>(left));

		rt::PointLight light({ -10, 10, -10 }, { 1,1,1 });
		w.set_light(std::make_shared<rt::PointLight>(light));

		m_camera.get()->transform() = rt::view_transform({ 0, 1.5f, -5 }, { 0,1,0 }, { 0,1,0 });

		auto canvas = m_camera.get()->render(w);
		return canvas;
	}

	void Sphere3::set_window_callback(app::Window& w) {
		m_camera.get()->set_pixel_callback([&w](int x, int y, float r, float g, float b) {
			w.pixel_changed(x, y, r, g, b);
		});
	}
}