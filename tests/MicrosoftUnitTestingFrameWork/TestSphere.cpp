#include "CppUnitTest.h"

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
			auto xs = s.intersects(r);
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

			auto xs = s.intersects(r);
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

			auto xs = s.intersects(r);
			Assert::IsTrue(xs.size() == 0);
		}


	};
}