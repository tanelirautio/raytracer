#include "CppUnitTest.h"

#include "../../src/rtMain.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestProject
{
	TEST_CLASS(TestIntersections)
	{
	public:
		TEST_METHOD(An_Intersection_Encapsulates_T_And_Object)
		{
			rt::Sphere s;
			rt::Intersection i(3.5f, &s);
			Assert::IsTrue(i.t == 3.5f);
			Assert::IsTrue(i.object == &s);
		}

		TEST_METHOD(Aggregating_Intersections)
		{
			rt::Sphere s;
			rt::Intersection i1(1, &s);
			rt::Intersection i2(2, &s);
			auto xs = rt::intersections(i1, i2);

			Assert::IsTrue(xs.size() == 2);
			Assert::IsTrue(xs[0].t == 1);
			Assert::IsTrue(xs[1].t == 2);
		}

		TEST_METHOD(Intersect_Sets_The_Object_On_The_Intersection)
		{
			rt::Ray r(rt::Point(0, 0, -5), rt::Vector(0, 0, 1));
			rt::Sphere s;
			auto xs = s.intersect(r);
			Assert::IsTrue(xs.size() == 2);
			Assert::IsTrue(xs[0].object == &s);
			Assert::IsTrue(xs[1].object == &s);
		}

		TEST_METHOD(Hit_When_All_Xs_Have_Positive_T)
		{
			rt::Sphere s;
			rt::Intersection i1(1, &s);
			rt::Intersection i2(2, &s);
			auto xs = rt::intersections(i2, i1);
			auto hit = s.hit(xs);
			Assert::AreEqual(hit.has_value(), true);
			Assert::IsTrue(hit.value() == i1);
		}

		TEST_METHOD(Hit_When_Some_Xs_Have_Negative_T)
		{
			rt::Sphere s;
			rt::Intersection i1(-1, &s);
			rt::Intersection i2(1, &s);
			auto xs = rt::intersections(i2, i1);
			auto hit = s.hit(xs);
			Assert::AreEqual(hit.has_value(), true);
			Assert::IsTrue(hit.value() == i2);
		}

		TEST_METHOD(Hit_When_All_Xs_Have_Negative_T)
		{
			rt::Sphere s;
			rt::Intersection i1(-2, &s);
			rt::Intersection i2(-1, &s);
			auto xs = rt::intersections(i2, i1);
			auto hit = s.hit(xs);
			Assert::AreEqual(hit.has_value(), false);
		}

		TEST_METHOD(Hit_Is_Always_The_Lowest_Nonnegative_Xs)
		{
			rt::Sphere s;
			rt::Intersection i1(5, &s);
			rt::Intersection i2(7, &s);
			rt::Intersection i3(-3, &s);
			rt::Intersection i4(2, &s);
			auto xs = rt::intersections(i1, i2, i3, i4);
			auto hit = s.hit(xs);
			Assert::AreEqual(hit.has_value(), true);
			Assert::IsTrue(hit.value() == i4);
		}
	};
}