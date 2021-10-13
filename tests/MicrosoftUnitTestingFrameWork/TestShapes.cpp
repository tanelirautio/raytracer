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

		TEST_METHOD(Computing_the_normal_on_a_translated_shape)
		{
			rt::TestShape s;
			s.transform() = rt::translation(0, 1, 0);
			auto n = s.normal_at({ 0, 1.70711f, -0.70711f });
			Assert::IsTrue(n == rt::Vector(0, 0.70711f, -0.70711f));
		}

		TEST_METHOD(Computing_the_normal_on_a_transformed_shape)
		{
			rt::TestShape s;
			rt::Matrix m = rt::scaling(1, 0.5f, 1) * rt::rotation_z((f32)M_PI / 5.f);
			s.transform() = m;
			auto n = s.normal_at({ 0, sqrt(2.f) / 2.f, -sqrt(2.f) / 2.f });
			Assert::IsTrue(n == rt::Vector(0, 0.97014f, -0.24254f));
		}
	};
}