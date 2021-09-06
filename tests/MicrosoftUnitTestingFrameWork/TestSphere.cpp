#include "CppUnitTest.h"

#include "../../src/rtDefs.hpp"
#include "../../src/rtRay.hpp"
#include "../../src/rtSphere.hpp"
#include "../../src/rtIntersection.hpp"
#include "../../src/rtTransformations.hpp"
#include "../../src/rtMatrix.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestProject
{
	TEST_CLASS(TestSphere)
	{
	public:
		TEST_METHOD(A_Ray_Intersects_A_Sphere_At_Two_Points)
		{
			rt::Ray ray(rt::Point(0,0,-5), rt::Vector(0,0,1));
			rt::Sphere s;

			auto xs = s.intersect(ray);
			Assert::IsTrue(xs.size() == 2);
			Assert::IsTrue(xs[0].t == 4.0f);
			Assert::IsTrue(xs[1].t == 6.0f);
		}

		TEST_METHOD(A_Ray_Intersects_A_Sphere_At_A_Tangent)
		{
			rt::Ray ray(rt::Point(0,1,-5), rt::Vector(0,0,1));
			rt::Sphere s;

			auto xs = s.intersect(ray);
			Assert::IsTrue(xs.size() == 2);
			Assert::IsTrue(xs[0].t == 5.0f);
			Assert::IsTrue(xs[1].t == 5.0f);
		}

		TEST_METHOD(A_Ray_Misses_A_Sphere)
		{
			rt::Ray ray(rt::Point(0,2,-5), rt::Vector(0,0,1));
			rt::Sphere s;

			auto xs = s.intersect(ray);
			Assert::IsTrue(xs.size() == 0);
		}

		TEST_METHOD(A_Ray_Originates_Inside_A_Sphere)
		{
			rt::Ray ray(rt::Point(0,0,0), rt::Vector(0,0,1));
			rt::Sphere s;

			auto xs = s.intersect(ray);
			Assert::IsTrue(xs.size() == 2);
			Assert::IsTrue(xs[0].t == -1.0f);
			Assert::IsTrue(xs[1].t == 1.0f);
		}
		
		TEST_METHOD(A_Sphere_Is_Behind_A_Ray)
		{
			rt::Ray ray(rt::Point(0,0,5), rt::Vector(0,0,1));
			rt::Sphere s;

			auto xs = s.intersect(ray);
			Assert::IsTrue(xs.size() == 2);
			Assert::IsTrue(xs[0].t == -6.0f);
			Assert::IsTrue(xs[1].t == -4.0f);
		}

		TEST_METHOD(A_Spheres_Default_Transformation)
		{		
			rt::Sphere s;
			Assert::IsTrue(s.get_transform() == rt::get_identity_matrix(4));
		}

		TEST_METHOD(Changing_A_Spheres_Transformation)
		{
			rt::Sphere s;
			rt::Matrix t = rt::translation(2, 3, 4);
			s.set_transform(t);
			Assert::IsTrue(s.get_transform() == t);
		}		
		
		TEST_METHOD(Intersecting_A_Scaled_Sphere_With_Ray)
		{
			rt::Ray r({ 0,0,-5 }, { 0,0,1 });
			rt::Sphere s;
			s.set_transform(rt::scaling(2, 2, 2));

			auto xs = s.intersect(r);
			auto hit = s.hit(xs);
			Assert::AreEqual(hit.has_value(), true);
			Assert::IsTrue(xs.size() == 2);
			Assert::IsTrue(xs[0].t = 3);
			Assert::IsTrue(xs[1].t = 7);
		}
		
		TEST_METHOD(Intersecting_A_Translated_Sphere_With_Ray)
		{
			rt::Ray r({ 0,0,-5 }, { 0,0,1 });
			rt::Sphere s;
			s.set_transform(rt::translation(5, 0, 0));

			auto xs = s.intersect(r);
			Assert::IsTrue(xs.size() == 0);
		}

		TEST_METHOD(The_Normal_On_A_Sphere_At_A_Point_On_The_X_Axis)
		{
			rt::Sphere s;
			rt::Vector n = s.normal_at({ 1, 0, 0 });
			Assert::IsTrue(n == rt::Vector(1, 0, 0));
		}

		TEST_METHOD(The_Normal_On_A_Sphere_At_A_Point_On_The_Y_Axis)
		{
			rt::Sphere s;
			rt::Vector n = s.normal_at({ 0, 1, 0 });
			Assert::IsTrue(n == rt::Vector(0, 1, 0));
		}

		TEST_METHOD(The_Normal_On_A_Sphere_At_A_Point_On_The_Z_Axis)
		{
			rt::Sphere s;
			rt::Vector n = s.normal_at({ 0, 0, 1 });
			Assert::IsTrue(n == rt::Vector(0, 0, 1));
		}

		TEST_METHOD(The_Normal_On_A_Sphere_At_A_Nonaxial_Point)
		{
			rt::Sphere s;
			rt::Vector n = s.normal_at({ sqrt(3.f) / 3.f, sqrt(3.f) / 3.f, sqrt(3.f) / 3.f });
			Assert::IsTrue(n == rt::Vector(sqrt(3.f) / 3.f, sqrt(3.f) / 3.f, sqrt(3.f) / 3.f));
		}
		
		/*
		TEST_METHOD(Computing_the_normal_on_a_translated_sphere)
		{
			rt::Sphere s;
			s.set_transform(rt::translation(0, 1, 0));
			rt::Vector n = s.normal_at(rt::Point(0, 1.70711f, -0.70711f));
			Assert::IsTrue(n == rt::Vector(0, 0.70711f, -0.70711f));
		}

		TEST_METHOD(Computing_the_normal_on_a_transformed_sphere)
		{
			rt::Sphere s;
			rt::Matrix m = rt::scaling(1, 0.5f, 1) * rt::rotation_z(M_PI / 5.f);
			s.set_transform(m);
			rt::Vector n = s.normal_at({ 0, sqrt(2.f) / 2.f, sqrtf(2.f) / 2.f });
			Assert::IsTrue(n == rt::Vector(0, 0.97014f, -0.24254f));
		}
		*/

	};
}