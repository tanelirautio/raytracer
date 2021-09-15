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
			Assert::IsTrue(w.get_objects().at(0) == s1);
			Assert::IsTrue(w.get_objects().at(1) == s2);
		}

		/*
		TEST_METHOD(Intersect_a_world_with_a_ray)
		{
			rt::World w = rt::get_default_world();
			rt::Ray r({ 0,0,-5 }, { 0,0,1 });

			auto xs = w.intersect(r);

			Assert::IsTrue(xs.size() == 4);
		}
		*/
	};
}