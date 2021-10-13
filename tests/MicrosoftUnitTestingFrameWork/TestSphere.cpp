#include "CppUnitTest.h"

#include "../../src/rtMain.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestProject
{
	TEST_CLASS(TestSphere)
	{
	public:
		TEST_METHOD(A_ray_intersects_a_sphere_at_two_points)
		{
			rt::Ray ray(rt::Point(0,0,-5), rt::Vector(0,0,1));
			rt::Sphere s;

			auto xs = s.local_intersect(ray);
			Assert::IsTrue(xs.size() == 2);
			Assert::IsTrue(xs[0].t == 4.0f);
			Assert::IsTrue(xs[1].t == 6.0f);
		}

		TEST_METHOD(A_ray_intersects_a_sphere_at_a_tangent)
		{
			rt::Ray ray(rt::Point(0,1,-5), rt::Vector(0,0,1));
			rt::Sphere s;

			auto xs = s.local_intersect(ray);
			Assert::IsTrue(xs.size() == 2);
			Assert::IsTrue(xs[0].t == 5.0f);
			Assert::IsTrue(xs[1].t == 5.0f);
		}

		TEST_METHOD(a_ray_misses_a_sphere)
		{
			rt::Ray ray(rt::Point(0,2,-5), rt::Vector(0,0,1));
			rt::Sphere s;

			auto xs = s.local_intersect(ray);
			Assert::IsTrue(xs.size() == 0);
		}

		TEST_METHOD(A_ray_originates_inside_a_sphere)
		{
			rt::Ray ray(rt::Point(0,0,0), rt::Vector(0,0,1));
			rt::Sphere s;

			auto xs = s.local_intersect(ray);
			Assert::IsTrue(xs.size() == 2);
			Assert::IsTrue(xs[0].t == -1.0f);
			Assert::IsTrue(xs[1].t == 1.0f);
		}
		
		TEST_METHOD(a_sphere_is_behind_a_ray)
		{
			rt::Ray ray(rt::Point(0,0,5), rt::Vector(0,0,1));
			rt::Sphere s;

			auto xs = s.local_intersect(ray);
			Assert::IsTrue(xs.size() == 2);
			Assert::IsTrue(xs[0].t == -6.0f);
			Assert::IsTrue(xs[1].t == -4.0f);
		}

		TEST_METHOD(A_spheres_default_transformation)
		{		
			rt::Sphere s;
			Assert::IsTrue(s.transform() == rt::get_identity_matrix(4));
		}

		TEST_METHOD(Changing_a_spheres_transformation)
		{
			rt::Sphere s;
			rt::Matrix t = rt::translation(2, 3, 4);
			s.transform() = t;
			Assert::IsTrue(s.transform() == t);
		}		

		TEST_METHOD(The_normal_on_a_sphere_at_a_point_on_the_x_axis)
		{
			rt::Sphere s;
			rt::Vector n = s.local_normal_at({ 1, 0, 0 });
			Assert::IsTrue(n == rt::Vector(1, 0, 0));
		}

		TEST_METHOD(The_normal_on_a_sphere_at_a_point_on_the_y_axis)
		{
			rt::Sphere s;
			rt::Vector n = s.local_normal_at({ 0, 1, 0 });
			Assert::IsTrue(n == rt::Vector(0, 1, 0));
		}

		TEST_METHOD(The_normal_on_a_sphere_at_a_point_on_the_z_Axis)
		{
			rt::Sphere s;
			rt::Vector n = s.local_normal_at({ 0, 0, 1 });
			Assert::IsTrue(n == rt::Vector(0, 0, 1));
		}

		TEST_METHOD(the_normal_on_a_sphere_at_a_nonaxial_point)
		{
			rt::Sphere s;
			rt::Vector n = s.local_normal_at({ sqrt(3.f) / 3.f, sqrt(3.f) / 3.f, sqrt(3.f) / 3.f });
			Assert::IsTrue(n == rt::Vector(sqrt(3.f) / 3.f, sqrt(3.f) / 3.f, sqrt(3.f) / 3.f));
		}
		
		TEST_METHOD(A_sphere_is_a_shape) 
		{
			rt::Sphere* sphere_ptr = new rt::Sphere();
			rt::Shape* shape_ptr = dynamic_cast<rt::Shape*>(sphere_ptr);
			Assert::IsNotNull(shape_ptr);
		}
	};
}