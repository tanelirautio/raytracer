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
			auto hit = rt::hit(xs);
			Assert::AreEqual(hit.has_value(), true);
			Assert::IsTrue(hit.value() == i1);
		}

		TEST_METHOD(Hit_When_Some_Xs_Have_Negative_T)
		{
			rt::Sphere s;
			rt::Intersection i1(-1, &s);
			rt::Intersection i2(1, &s);
			auto xs = rt::intersections(i2, i1);
			auto hit = rt::hit(xs);
			Assert::AreEqual(hit.has_value(), true);
			Assert::IsTrue(hit.value() == i2);
		}

		TEST_METHOD(Hit_When_All_Xs_Have_Negative_T)
		{
			rt::Sphere s;
			rt::Intersection i1(-2, &s);
			rt::Intersection i2(-1, &s);
			auto xs = rt::intersections(i2, i1);
			auto hit = rt::hit(xs);
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
			auto hit = rt::hit(xs);
			Assert::AreEqual(hit.has_value(), true);
			Assert::IsTrue(hit.value() == i4);
		}

		TEST_METHOD(Precomputing_the_state_of_an_intersection)
		{
			rt::Ray r({ 0,0,-5 }, { 0,0,1 });
			rt::Sphere s;
			rt::Intersection i(4, &s);
			rt::Computations comps = rt::prepare_computations(i, r);
			Assert::IsTrue(comps.t == i.t);
			Assert::IsTrue(comps.object == i.object);
			Assert::IsTrue(comps.point == rt::Point(0,0,-1));
			Assert::IsTrue(comps.eyev == rt::Vector(0,0,-1));
			Assert::IsTrue(comps.normalv == rt::Vector(0,0,-1));
		}

		TEST_METHOD(The_hit_when_an_intersection_occurs_on_the_outside)
		{
			rt::Ray r({ 0,0,-5 }, { 0,0,1 });
			rt::Sphere s;
			rt::Intersection i(4, &s);
			rt::Computations comps = rt::prepare_computations(i, r);
			Assert::AreEqual(comps.inside, false);
		}

		TEST_METHOD(The_hit_when_an_intersection_occurs_on_the_inside)
		{
			rt::Ray r({ 0,0,0 }, { 0,0,1 });
			rt::Sphere s;
			rt::Intersection i(1, &s);
			rt::Computations comps = rt::prepare_computations(i, r);
			Assert::IsTrue(comps.point == rt::Point(0, 0, 1));
			Assert::IsTrue(comps.eyev == rt::Vector(0, 0, -1));
			//normal would have been (0,0,1), but it's inverted!
			Assert::IsTrue(comps.normalv == rt::Vector(0, 0, -1));
			Assert::AreEqual(comps.inside, true);
		}

		TEST_METHOD(The_hit_should_offset_the_point)
		{
			rt::Ray r({ 0,0,-5 }, { 0,0,1 });
			rt::Sphere s;
			s.transform() = rt::translation(0, 0, 1);
			rt::Intersection i(5, &s);
			rt::Computations comps = rt::prepare_computations(i, r);
			Assert::IsTrue(comps.over_point.z < -EPSILON/2.f);
			Assert::IsTrue(comps.point.z > comps.over_point.z);
		}

		TEST_METHOD(Precomputing_the_reflection_vector)
		{
			rt::Plane p;
			rt::Ray r({ 0, 1, -1 }, { 0, -std::sqrt(2.f) / 2.f, std::sqrt(2.f) / 2.f } );
			rt::Intersection i(std::sqrt(2.f), &p);
			rt::Computations comps = rt::prepare_computations(i, r);
			Assert::IsTrue(comps.reflectv == rt::Vector(0, std::sqrt(2.f) / 2.f, std::sqrt(2.f) / 2.f));
		}

		TEST_METHOD(Finding_n1_and_n2_at_various_intersections)
		{
			rt::Sphere a = rt::Sphere::glass();
			a.transform() = rt::scaling(2, 2, 2);
			a.material().refractive_index = 1.5f;

			rt::Sphere b = rt::Sphere::glass();
			b.transform() = rt::translation(0, 0, -0.25f);
			b.material().refractive_index = 2.0f;

			rt::Sphere c = rt::Sphere::glass();
			c.transform() = rt::translation(0, 0, 0.25f);
			c.material().refractive_index = 2.5f;

			rt::Ray r({ 0, 0, -4 }, { 0, 0, 1 });
			std::vector<rt::Intersection> xs{
				{ 2.0f, &a },
				{ 2.75f, &b },
				{ 3.25f, &c },
				{ 4.75f, &b },
				{ 5.25f, &c },
				{ 6.f, &a }
			};

			const float expected_n1[] = { 1.0f, 1.5f, 2.0f, 2.5f, 2.5f, 1.5f };
			const float expected_n2[] = { 1.5f, 2.0f, 2.5f, 2.5f, 1.5f, 1.0f };

			for (int index = 0; index < 6; ++index) {
				rt::Computations comps =
					rt::prepare_computations(xs[index], r, xs);

				Assert::IsTrue(rt::equal(comps.n1, expected_n1[index]));
				Assert::IsTrue(rt::equal(comps.n2, expected_n2[index]));
			}

		}

	};
}
