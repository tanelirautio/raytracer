#include "CppUnitTest.h"

#include "../../src/rtMain.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestProject
{
	TEST_CLASS(TestWorld)
	{
	public:
		TEST_METHOD(Create_a_world)
		{
			rt::World w;
			Assert::IsTrue(w.get_lights().size() == 0);
			Assert::IsTrue(w.get_objects().size() == 0);
		}

		
		TEST_METHOD(Create_a_default_world)
		{
			rt::PointLight light({ -10,10,-10 }, { 1,1,1 });

			rt::Material m1;
			m1.color = { 0.8f, 1.0f, 0.6f };
			m1.diffuse = 0.7f;
			m1.specular = 0.2f;
			rt::Sphere s1;
			s1.material() = m1;

			rt::Matrix t1 = rt::scaling(0.5f, 0.5f, 0.5f);
			rt::Sphere s2;
			s2.transform() = t1;

			rt::World w = rt::get_default_world();
			Assert::IsTrue(w.get_lights().size() == 1);
			Assert::IsTrue(w.get_objects().size() == 2);

			Assert::IsTrue(*w.get_lights().at(0).get() == light);
			Assert::IsTrue(*w.get_objects().at(0).get() == s1);
			Assert::IsTrue(*w.get_objects().at(1).get() == s2);
		}

		TEST_METHOD(Intersect_a_world_with_a_ray)
		{
			rt::World w = rt::get_default_world();
			rt::Ray r({ 0,0,-5 }, { 0,0,1 });

			auto xs = w.intersect(r);
			Assert::IsTrue(xs.size() == 4);
			Assert::IsTrue(xs[0].t == 4.f);
			Assert::IsTrue(xs[1].t == 4.5f);
			Assert::IsTrue(xs[2].t == 5.5f);
			Assert::IsTrue(xs[3].t == 6.f);
		}

		
		TEST_METHOD(Shading_an_intersection)
		{
			rt::World w = rt::get_default_world();
			rt::Ray r({ 0,0,-5 }, { 0,0,1 });
			auto shape = w.get_objects().at(0);

			Assert::IsTrue(*w.get_lights().at(0).get() == rt::PointLight({ -10,10,-10 }, { 1,1,1 }));

			rt::Intersection i(4, shape.get());
			rt::Computations comps = rt::prepare_computations(i, r);

			Assert::IsTrue(comps.t == i.t);
			Assert::IsTrue(comps.object == i.object);
			Assert::IsTrue(comps.point == rt::Point(0, 0, -1));
			Assert::IsTrue(comps.eyev == rt::Vector(0, 0, -1));
			Assert::IsTrue(comps.normalv == rt::Vector(0, 0, -1));

			rt::Material m = comps.object->material();
			Assert::IsTrue(m.color == rt::Color(0.8f, 1.0f, 0.6f));
			Assert::IsTrue(m.diffuse == 0.7f);
			Assert::IsTrue(m.specular == 0.2f);

			rt::Color c = w.shade_hit(comps);
			Assert::IsTrue(c == rt::Color(0.38066f, 0.47583f, 0.2855f));
		}
		
		TEST_METHOD(Shading_an_intersection_from_the_inside)
		{
			rt::World w = rt::get_default_world();
			auto l = std::make_shared<rt::PointLight>(rt::Point(0, 0.25f, 0), rt::Vector(1, 1, 1));
			w.set_light(l, true); // if true, remove already existing lights
			rt::Ray r({ 0,0,0 }, { 0,0,1 });
			auto shape = w.get_objects().at(1);
			rt::Intersection i(0.5f, shape.get());
			rt::Computations comps = rt::prepare_computations(i, r);
			rt::Color c = w.shade_hit(comps);
			Assert::IsTrue(c == rt::Color(0.90498f, 0.90498f, 0.90498f));
		}

		TEST_METHOD(The_color_when_a_ray_misses)
		{
			rt::World w = rt::get_default_world();
			rt::Ray r({ 0,0,-5 }, { 0,1,0 });
			rt::Color c = w.color_at(r);
			Assert::IsTrue(c == rt::Color(0,0,0));
		}

		TEST_METHOD(The_color_when_a_ray_hits)
		{
			rt::World w = rt::get_default_world();
			rt::Ray r({ 0,0,-5 }, { 0,0,1 });
			rt::Color c = w.color_at(r);
			Assert::IsTrue(c == rt::Color(0.38066f, 0.47583f, 0.2855f));
		}

		TEST_METHOD(The_color_with_an_intersection_behind_the_ray)
		{
			rt::World w = rt::get_default_world();
			auto outer = w.get_objects().at(0);
			outer.get()->material().ambient = 1;

			auto inner = w.get_objects().at(1);
			auto m2 = inner.get()->material().ambient = 1;

			rt::Ray r({ 0,0,0.75f }, { 0,0,-1 });
			rt::Color c = w.color_at(r);
			Assert::IsTrue(c == inner.get()->material().color);
		}

		TEST_METHOD(There_is_no_shadow_when_nothing_is_collinear_with_point_and_light)
		{
			rt::World w = rt::get_default_world();
			auto p = rt::Point(0, 10, 0);
			Assert::IsTrue(w.is_shadowed(p) == false);
		}

		TEST_METHOD(The_shadow_when_an_object_is_between_the_point_and_the_light)
		{
			rt::World w = rt::get_default_world();
			auto p = rt::Point(10, -10, 10);
			Assert::IsTrue(w.is_shadowed(p) == true);
		}

		TEST_METHOD(There_is_no_shadow_when_an_object_is_behind_the_light)
		{
			rt::World w = rt::get_default_world();
			auto p = rt::Point(-20, 20, -20);
			Assert::IsTrue(w.is_shadowed(p) == false);
		}

		TEST_METHOD(There_is_no_shadow_when_an_object_is_behind_the_point)
		{
			rt::World w = rt::get_default_world();
			auto p = rt::Point(-2, 2, -2);
			Assert::IsTrue(w.is_shadowed(p) == false);
		}

		TEST_METHOD(Shade_hit_function_is_given_an_intersection_in_shadow)
		{
			rt::World w;
			w.set_light(std::make_shared<rt::PointLight>(rt::Point(0, 0, -10), rt::Vector(1, 1, 1)));

			auto s1 = std::make_shared<rt::Sphere>();
			w.set_object(s1);

			auto s2 = std::make_shared<rt::Sphere>();
			s2->transform() = rt::translation(0, 0, 10);
			w.set_object(s2);

			auto r = rt::Ray({ 0,0,5 }, { 0,0,1 });
			rt::Intersection i(4, s2.get());

			auto comps = rt::prepare_computations(i, r);
			auto c = w.shade_hit(comps);

			Assert::IsTrue(c == rt::Color(0.1f, 0.1f, 0.1f));
		}
	};
}