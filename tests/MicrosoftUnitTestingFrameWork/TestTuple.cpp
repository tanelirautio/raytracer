#include "CppUnitTest.h"

#include "../../src/rtMain.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestProject
{
	TEST_CLASS(TestTuple)
	{
	public:
		
		TEST_METHOD(An_empty_tuple_returns_zero)
		{
			rt::Tuple a;
			Assert::AreEqual(a.x, 0.0f);
			Assert::AreEqual(a.y, 0.0f);
			Assert::AreEqual(a.z, 0.0f);
			Assert::AreEqual(a.z, 0.0f);
			Assert::AreEqual(a.w, 0.0f);
		}

		TEST_METHOD(A_tuple_with_w_1_is_a_point)
		{
			rt::Tuple a(4.3f, -4.2f, 3.1f, 1.0f);
			Assert::AreEqual(a.x, 4.3f);
			Assert::AreEqual(a.y, -4.2f);
			Assert::AreEqual(a.z, 3.1f);
			Assert::AreEqual(a.w, 1.0f);
			Assert::AreEqual(a.is_point(), true);
		}

		TEST_METHOD(A_tuple_with_w_0_is_a_vector)
		{
			rt::Tuple a(4.3f, -4.2f, 3.1f, 0.0f);
			Assert::AreEqual(a.x, 4.3f);
			Assert::AreEqual(a.y, -4.2f);
			Assert::AreEqual(a.z, 3.1f);
			Assert::AreEqual(a.w, 0.0f);
			Assert::AreEqual(a.is_vector(), true);
		}
			
		TEST_METHOD(Point_creates_tuples_with_w_1)
		{
			rt::Point p(4, -4, 3);
			rt::Tuple t(4, -4, 3, 1);
			Assert::IsTrue(p == t);
			Assert::AreEqual(p.is_point(), true);
		}		
		
		TEST_METHOD(Vector_creates_tuples_with_w_0)
		{
			rt::Vector v(4, -4, 3);
			rt::Tuple t(4, -4, 3, 0);
			Assert::IsTrue(v == t);
			Assert::AreEqual(v.is_vector(), true);
		}

		TEST_METHOD(Adding_two_tuples)
		{
			rt::Tuple a1(3, -2, 5, 1);
			rt::Tuple a2(-2, 3, 1, 0);
			rt::Tuple a3 = a1 + a2;
			Assert::IsTrue(a3 == rt::Tuple(1, 1, 6, 1));
		}		
		
		TEST_METHOD(Substracting_two_points)
		{
			rt::Point p1(3, 2, 1);
			rt::Point p2(5, 6, 7);
			rt::Tuple t1 = p1 - p2;
			Assert::IsTrue(t1 == rt::Tuple(-2, -4, -6, 0));
			Assert::AreEqual(t1.is_vector(), true);
		}
		
		TEST_METHOD(Subtracting_a_vector_from_point)
		{
			rt::Point p1(3, 2, 1);
			rt::Vector v1(5, 6, 7);
			rt::Tuple t1 = p1 - v1;
			Assert::IsTrue(t1 == rt::Tuple(-2, -4, -6, 1));
			Assert::AreEqual(t1.is_point(), true);
		}
		
		TEST_METHOD(Subracting_two_vectors)
		{
			rt::Vector v1(3, 2, 1);
			rt::Vector v2(5, 6, 7);
			rt::Tuple t1 = v1 - v2;
			Assert::IsTrue(t1 == rt::Tuple(-2, -4, -6, 0));
			Assert::AreEqual(t1.is_vector(), true);
		}

		TEST_METHOD(Subtracting_a_vector_from_the_zero_vector)
		{
			rt::Vector zero(0, 0, 0);
			rt::Vector v1(1, -2, 3);
			rt::Tuple t1 = zero - v1;
			Assert::IsTrue(t1 == rt::Vector(-1, 2, -3));
			Assert::AreEqual(t1.is_vector(), true);
		}

		TEST_METHOD(Negating_a_tuple)
		{
			rt::Tuple t1(1, -2, 3, -4);
			rt::Tuple t2 = -t1;
			Assert::IsTrue(t2 == rt::Tuple(-1.0f, 2.0f, -3.0f, 4.0f));
		}

		TEST_METHOD(Multiplying_a_tuple_by_a_scalar)
		{
			rt::Tuple t1(1, -2, 3, -4);
			rt::Tuple t2 = t1 * 3.5f;
			Assert::IsTrue(t2 == rt::Tuple(3.5f, -7.0f, 10.5f, -14.0f));
		}

		TEST_METHOD(Multiplying_a_tuple_by_a_fraction)
		{
			rt::Tuple t1(1, -2, 3, -4);
			rt::Tuple t2 = t1 * 0.5f;
			Assert::IsTrue(t2 == rt::Tuple(0.5f, -1.0f, 1.5f, -2.0f));
		}

		TEST_METHOD(Dividing_a_tuple_by_a_scalar)
		{
			rt::Tuple t1(1, -2, 3, -4);
			rt::Tuple t2 = t1 / 2;
			Assert::IsTrue(t2 == rt::Tuple(0.5f, -1.0f, 1.5f, -2.0f));
		}

		TEST_METHOD(Computing_the_magnitude_of_different_vectors)
		{
			rt::Vector v1(1, 0, 0);
			Assert::AreEqual(v1.magnitude(), 1.0f);

			rt::Vector v2(0, 1, 0);
			Assert::AreEqual(v2.magnitude(), 1.0f);

			rt::Vector v3(0, 0, 1);
			Assert::AreEqual(v3.magnitude(), 1.0f);

			rt::Vector v4(1, 2, 3);
			Assert::AreEqual(v4.magnitude(), std::sqrt(14.0f));

			rt::Vector v5(-1, -2, -3);
			Assert::AreEqual(v5.magnitude(), std::sqrt(14.0f));
		}

		TEST_METHOD(Normalizing_vector_4_0_0_gives_1_0_0)
		{
			rt::Vector v1(4, 0, 0);

			rt::Tuple r1 = v1.normalize();
			Assert::IsTrue(r1 == rt::Tuple(1, 0, 0, 0));

			rt::Vector r2 = v1.normalize();
			Assert::IsTrue(r2 == rt::Vector(1, 0, 0));

			rt::Vector v2(1, 2, 3);
			rt::Vector r3 = v2.normalize();
			Assert::AreEqual(r3.x, 1.0f/sqrt(14.0f));
			Assert::AreEqual(r3.y, 2.0f/sqrt(14.0f));
			Assert::AreEqual(r3.z, 3.0f/sqrt(14.0f));
		}

		TEST_METHOD(The_magnitude_of_a_normalized_vector)
		{
			rt::Vector v1(4, 0, 0);
			rt::Vector r1 = v1.normalize();
			Assert::AreEqual(r1.magnitude(), 1.0f);
		}

		TEST_METHOD(The_dot_product_of_two_tuples) 
		{
			rt::Vector v1(1, 2, 3);
			rt::Vector v2(2, 3, 4);
			Assert::AreEqual(v1.dot(v2), 20.0f);
		}		
		
		TEST_METHOD(The_cross_product_of_two_vectors) 
		{
			rt::Vector v1(1, 2, 3);
			rt::Vector v2(2, 3, 4);

			rt::Vector r1 = v1.cross(v2);
			Assert::IsTrue(r1 == rt::Vector(-1, 2, -1));

			rt::Vector r2 = v2.cross(v1);
			Assert::IsTrue(r2 == rt::Vector(1, -2, 1));
		}

		TEST_METHOD(Colors_are_red_green_blue_tuples)
		{
			rt::Color c(-0.5f, 0.4f, 1.7f);
			Assert::AreEqual(c.r, -0.5f);
			Assert::AreEqual(c.g, 0.4f);
			Assert::AreEqual(c.b, 1.7f);
		}

		TEST_METHOD(Adding_colors)
		{
			rt::Color c1(0.9f, 0.6f, 0.75f);
			rt::Color c2(0.7f, 0.1f, 0.25f);
			Assert::IsTrue(c1 + c2 == rt::Color(1.6f, 0.7f, 1.0f));
		}

		TEST_METHOD(Substracting_colors)
		{
			rt::Color c1(0.9f, 0.6f, 0.75f);
			rt::Color c2(0.7f, 0.1f, 0.25f);
			Assert::IsTrue(c1 - c2 == rt::Color(0.2f, 0.5f, 0.5f));
		}

		TEST_METHOD(Multiplying_a_color_by_a_scalar)
		{
			rt::Color c(0.2f, 0.3f, 0.4f);
			Assert::IsTrue(c*2 == rt::Color(0.4f, 0.6f, 0.8f));
		}

		TEST_METHOD(Multiplying_colors)
		{
			rt::Color c1(1.0f, 0.2f, 0.4f);
			rt::Color c2(0.9f, 1.0f, 0.1f);
			Assert::IsTrue(c1*c2 == rt::Color(0.9f, 0.2f, 0.04f));
		}

		TEST_METHOD(Reflecting_a_vector_approaching_at_45_degrees)
		{
			rt::Vector v(1, -1, 0);
			rt::Vector n(0, 1, 0);
			rt::Vector r = v.reflect(n);
			Assert::IsTrue(r == rt::Vector(1,1,0));
		}

		TEST_METHOD(Reflecting_a_vector_off_a_slanted_surface)
		{
			rt::Vector v(0, -1, 0);
			rt::Vector n(sqrt(2.f)/2.f, sqrt(2.f)/2.f, 0);
			rt::Vector r = v.reflect(n);
			Assert::IsTrue(r == rt::Vector(1, 0, 0));
		}
	};
}
