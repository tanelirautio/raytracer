#include "CppUnitTest.h"

#include "../../src/rtRay.hpp"
#include "../../src/rtSphere.hpp"
#include "../../src/rtIntersection.hpp"

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

			auto xs = s.intersects(ray);
			Assert::IsTrue(xs.size() == 2);
			Assert::IsTrue(xs[0].t == 4.0f);
			Assert::IsTrue(xs[1].t == 6.0f);
		}

		TEST_METHOD(A_Ray_Intersects_A_Sphere_At_A_Tangent)
		{
			rt::Ray ray(rt::Point(0,1,-5), rt::Vector(0,0,1));
			rt::Sphere s;

			auto xs = s.intersects(ray);
			Assert::IsTrue(xs.size() == 2);
			Assert::IsTrue(xs[0].t == 5.0f);
			Assert::IsTrue(xs[1].t == 5.0f);
		}

		TEST_METHOD(A_Ray_Misses_A_Sphere)
		{
			rt::Ray ray(rt::Point(0,2,-5), rt::Vector(0,0,1));
			rt::Sphere s;

			auto xs = s.intersects(ray);
			Assert::IsTrue(xs.size() == 0);
		}

		TEST_METHOD(A_Ray_Originates_Inside_A_Sphere)
		{
			rt::Ray ray(rt::Point(0,0,0), rt::Vector(0,0,1));
			rt::Sphere s;

			auto xs = s.intersects(ray);
			Assert::IsTrue(xs.size() == 2);
			Assert::IsTrue(xs[0].t == -1.0f);
			Assert::IsTrue(xs[1].t == 1.0f);
		}
		
		TEST_METHOD(A_Sphere_Is_Behind_A_Ray)
		{
			rt::Ray ray(rt::Point(0,0,5), rt::Vector(0,0,1));
			rt::Sphere s;

			auto xs = s.intersects(ray);
			Assert::IsTrue(xs.size() == 2);
			Assert::IsTrue(xs[0].t == -6.0f);
			Assert::IsTrue(xs[1].t == -4.0f);
		}

		TEST_METHOD(An_Intersection_Encapsulates_T_And_Object)
		{
			rt::Sphere s;
			rt::Intersection i(3.5f, &s);
			Assert::IsTrue(i.t == 3.5f);
			Assert::IsTrue(i.object == &s);
		}
	};
}