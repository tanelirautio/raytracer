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
			rt::PointLight light({ -10,10,10 }, { 1,1,1 });

			rt::Material m1;
			m1.color({ 0.8f, 1.0f, 0.6f });
			m1.diffuse(0.7f);
			m1.specular(0.2f);
			rt::Sphere s1;
			s1.set_material(m1);

			rt::Matrix t1 = rt::scaling(0.5f, 0.5f, 0.5f);
			rt::Sphere s2;
			s2.set_transform(t1);

			rt::World w = rt::get_default_world();
			Assert::IsTrue(w.get_lights().size() == 1);
			Assert::IsTrue(w.get_objects().size() == 2);

			Assert::IsTrue(w.get_lights().at(0) == light);
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

		/*
		TEST_METHOD(Shading_an_intersection)
		{
			rt::World w = rt::get_default_world();
			rt::Ray r({ 0,0,-5 }, { 0,0,1 });
			auto shape = w.get_objects().at(0);
			rt::Intersection i(4, shape.get());
			rt::Computations comps = rt::prepare_computations(i, r);
			rt::Color c = w.shade_hit(comps);
			Assert::IsTrue(c == rt::Color(0.38066f, 0.47583f, 0.2855f));
		}

		TEST_METHOD(Shading_an_intersection_from_the_inside)
		{
			rt::World w = rt::get_default_world();
			w.set_light(rt::PointLight({ 0,0.25f,0 }, { 1,1,1 }));
			rt::Ray r({ 0,0,0 }, { 0,0,1 });
			auto shape = w.get_objects().at(1);
			rt::Intersection i(0.5f, shape.get());
			rt::Computations comps = rt::prepare_computations(i, r);
			rt::Color c = w.shade_hit(comps);
			Assert::IsTrue(c == rt::Color(0.90498f, 0.90498f, 0.90498f));
		}
		*/

	};
}