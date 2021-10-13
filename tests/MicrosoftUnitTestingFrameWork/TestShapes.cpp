#include "CppUnitTest.h"

#include "../../src/rtMain.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestProject
{
	TEST_CLASS(TestShape)
	{
	public:
		TEST_METHOD(The_default_transformation)
		{
			rt::TestShape s;
			Assert::IsTrue(s.transform() == rt::get_identity_matrix4());
		}

		TEST_METHOD(Assigning_a_transformation)
		{
			rt::TestShape s;
			s.transform() = rt::translation(2, 3, 4);
			Assert::IsTrue(s.transform() == rt::translation(2, 3, 4));
		}

		TEST_METHOD(The_default_material)
		{
			rt::TestShape s;
			auto& m = s.material();
			Assert::IsTrue(m == rt::Material());
		}

		TEST_METHOD(Assigning_a_material)
		{
			rt::TestShape s;
			auto m = s.material();
			m.ambient = 1;
			s.material() = m;
			Assert::IsTrue(s.material() == m);
		}

		TEST_METHOD(Intersecting_a_scaled_shape_with_a_ray)
		{
			rt::TestShape s;
			rt::Ray r({ 0,0,-5 }, { 0,0,1 });
			s.transform() = rt::scaling(2, 2, 2);
			auto xs = s.intersect(r);
			Assert::IsTrue(s.get_saved_ray().origin() == rt::Point(0, 0, -2.5f));
			Assert::IsTrue(s.get_saved_ray().direction() == rt::Vector(0, 0, 0.5f));
		}

		TEST_METHOD(Intersecting_a_translated_shape_with_a_ray)
		{
			rt::TestShape s;
			rt::Ray r({ 0,0,-5 }, { 0,0,1 });
			s.transform() = rt::translation(5, 0, 0);
			auto xs = s.intersect(r);
			Assert::IsTrue(s.get_saved_ray().origin() == rt::Point(-5, 0, -5));
			Assert::IsTrue(s.get_saved_ray().direction() == rt::Vector(0, 0, 1));
		}


	};
}