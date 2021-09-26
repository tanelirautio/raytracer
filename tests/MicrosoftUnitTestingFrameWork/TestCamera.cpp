#include "CppUnitTest.h"

#include "../../src/rtMain.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestProject
{
	TEST_CLASS(TestCamera)
	{
	public:

		TEST_METHOD(Constructing_a_camera)
		{
			rt::Camera c(160, 120, (f32)M_PI / 2.f);
			Assert::IsTrue(c.hsize() == 160);
			Assert::IsTrue(c.vsize() == 120);
			Assert::IsTrue(c.fov() == HALF_PI);
			Assert::IsTrue(c.transform() == rt::get_identity_matrix4());
		}

		TEST_METHOD(The_pixel_size_for_a_horizontal_canvas)
		{
			rt::Camera c(200, 125, HALF_PI);
			Assert::IsTrue(c.pixel_size() == 0.01f);
		}

		TEST_METHOD(The_pixel_size_for_a_vertical_canvas)
		{
			rt::Camera c(125, 200, HALF_PI);
			Assert::IsTrue(c.pixel_size() == 0.01f);
		}

		TEST_METHOD(Constructing_a_ray_through_the_center_of_the_canvas)
		{
			rt::Camera c(201, 101, HALF_PI);
			rt::Ray r = c.ray_for_pixel(100, 50);
			Assert::IsTrue(r.origin() == rt::Point(0, 0, 0));
			Assert::IsTrue(r.direction() == rt::Vector(0, 0, -1));
		}

		TEST_METHOD(Constructing_a_ray_through_the_corner_of_the_canvas)
		{
			rt::Camera c(201, 101, HALF_PI);
			rt::Ray r = c.ray_for_pixel(0, 0);
			Assert::IsTrue(r.origin() == rt::Point(0, 0, 0));
			Assert::IsTrue(r.direction() == rt::Vector(0.66519f, 0.33259f, -0.66851f));
		}

		TEST_METHOD(Constructing_a_ray_when_the_camera_is_transformed)
		{
			rt::Camera c(201, 101, HALF_PI);
			c.transform() = rt::rotation_y(M_PI / 4.f) * rt::translation(0, -2, 5);
			rt::Ray r = c.ray_for_pixel(100, 50);
			Assert::IsTrue(r.origin() == rt::Point(0, 2, -5));
			Assert::IsTrue(r.direction() == rt::Vector(sqrt(2.f)/2.f, 0, -sqrt(2.f) / 2.f));
		}

		TEST_METHOD(Rendering_a_world_with_camera)
		{
			rt::World w = rt::get_default_world();
			rt::Camera c(11, 11, HALF_PI);
			auto from = rt::Point(0, 0, -5);
			auto to = rt::Point(0, 0, 0);
			auto up = rt::Vector(0, 1, 0);
			c.transform() = rt::view_transform(from, to, up);
			auto image = c.render(w);
			Assert::IsTrue(image.pixel_at(5, 5) == rt::Color(0.38066f, 0.47583f, 0.2855f));
		}


	};
}