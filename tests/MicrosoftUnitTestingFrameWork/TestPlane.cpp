#include "CppUnitTest.h"

#include "../../src/rtMain.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestProject
{
	TEST_CLASS(TestPlane)
	{
	public:
		TEST_METHOD(The_normal_of_a_plane_is_constant_everywhere)
		{
			rt::Plane p;
			auto n1 = p.local_normal_at({ 0, 0, 0 });
			auto n2 = p.local_normal_at({ 10, 0, -10 });
			auto n3 = p.local_normal_at({ -5, 0, 150 });
			Assert::IsTrue(n1 == rt::Vector(0, 1, 0));
			Assert::IsTrue(n2 == rt::Vector(0, 1, 0));
			Assert::IsTrue(n3 == rt::Vector(0, 1, 0));
		}

		TEST_METHOD(Intersect_with_a_ray_parallel_to_the_plane)
		{
			rt::Plane p;
			rt::Ray r({ 0, 10, 0 }, { 0, 0, 1 });
			auto xs = p.local_intersect(r);
			Assert::IsTrue(xs.size() == 0);
		}
		
		TEST_METHOD(Intersect_with_a_coplanar_ray)
		{
			rt::Plane p;
			rt::Ray r({ 0, 0, 0 }, { 0, 0, 1 });
			auto xs = p.local_intersect(r);
			Assert::IsTrue(xs.size() == 0);
		}

		TEST_METHOD(A_ray_intersecting_a_plane_from_above)
		{
			rt::Plane p;
			rt::Ray r({ 0, 1, 0 }, { 0, -1, 0});
			auto xs = p.local_intersect(r);
			Assert::IsTrue(xs.size() == 1);
			Assert::IsTrue(xs[0].t == 1);
			Assert::IsTrue(xs[0].object == &p);
		}
		
		TEST_METHOD(A_ray_intersecting_a_plane_from_below)
		{
			rt::Plane p;
			rt::Ray r({ 0, -1, 0 }, { 0, 1, 0 });
			auto xs = p.local_intersect(r);
			Assert::IsTrue(xs.size() == 1);
			Assert::IsTrue(xs[0].t == 1);
			Assert::IsTrue(xs[0].object == &p);
		}


	};
}