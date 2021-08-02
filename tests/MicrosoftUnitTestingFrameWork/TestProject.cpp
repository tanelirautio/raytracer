#include "pch.h"
#include "CppUnitTest.h"

#include "../../src/rtTuple.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestProject
{
	TEST_CLASS(TestTuple)
	{
	public:
		
		TEST_METHOD(Tuple_EmptyReturnsZero)
		{
			rt::Tuple a;
			Assert::AreEqual(a.x(), 0.0f);
			Assert::AreEqual(a.y(), 0.0f);
			Assert::AreEqual(a.z(), 0.0f);
			Assert::AreEqual(a.w(), 0.0f);
		}

		TEST_METHOD(Tuple_W1IsPoint)
		{
			rt::Tuple a(4.3f, -4.2f, 3.1f, 1.0f);
			Assert::AreEqual(a.x(), 4.3f);
			Assert::AreEqual(a.y(), -4.2f);
			Assert::AreEqual(a.z(), 3.1f);
			Assert::AreEqual(a.w(), 1.0f);
			Assert::AreEqual(a.isPoint(), true);
		}

		TEST_METHOD(Tuple_PointCreateTuplesWithW1)
		{
			rt::Point p(4, -4, 3);
			rt::Tuple t(4, -4, 3, 1);
			Assert::IsTrue(p == t);
			Assert::AreEqual(p.isPoint(), true);
		}		
		
		TEST_METHOD(Tuple_VectorCreateTuplesWithW0)
		{
			rt::Vector v(4, -4, 3);
			rt::Tuple t(4, -4, 3, 0);
			Assert::IsTrue(v == t);
			Assert::AreEqual(v.isVector(), true);
		}

		TEST_METHOD(Tuple_AddTwoTuples)
		{
			rt::Tuple a1(3, -2, 5, 1);
			rt::Tuple a2(-2, 3, 1, 0);
			rt::Tuple a3 = a1 + a2;
			Assert::IsTrue(a3 == rt::Tuple(1, 1, 6, 1));
		}		
		
		TEST_METHOD(Tuple_SubtractTwoPoints)
		{
			rt::Point p1(3, 2, 1);
			rt::Point p2(5, 6, 7);
			rt::Tuple t1 = p1 - p2;
			Assert::IsTrue(t1 == rt::Tuple(-2, -4, -6, 0));
			Assert::AreEqual(t1.isVector(), true);
		}
		
		TEST_METHOD(Tuple_SubtractVectorFromPoint)
		{
			rt::Point p1(3, 2, 1);
			rt::Vector v1(5, 6, 7);
			rt::Tuple t1 = p1 - v1;
			Assert::IsTrue(t1 == rt::Tuple(-2, -4, -6, 1));
			Assert::AreEqual(t1.isPoint(), true);
		}
		
		TEST_METHOD(Tuple_SubtractTwoVectors)
		{
			rt::Vector v1(3, 2, 1);
			rt::Vector v2(5, 6, 7);
			rt::Tuple t1 = v1 - v2;
			Assert::IsTrue(t1 == rt::Tuple(-2, -4, -6, 0));
			Assert::AreEqual(t1.isVector(), true);
		}

		TEST_METHOD(Tuple_SubtractVectorFromZeroVector)
		{
			rt::Vector zero(0, 0, 0);
			rt::Vector v1(1, -2, 3);
			rt::Tuple t1 = zero - v1;
			Assert::IsTrue(t1 == rt::Vector(-1, 2, -3));
			Assert::AreEqual(t1.isVector(), true);
		}

		TEST_METHOD(Tuple_Negate)
		{
			rt::Tuple t1(1, -2, 3, -4);
			rt::Tuple t2 = -t1;
			Assert::IsTrue(t2 == rt::Tuple(-1.0f, 2.0f, -3.0f, 4.0f));
		}

		TEST_METHOD(Tuple_MultiplyWithScalar)
		{
			rt::Tuple t1(1, -2, 3, -4);
			rt::Tuple t2 = t1 * 3.5f;
			Assert::IsTrue(t2 == rt::Tuple(3.5f, -7.0f, 10.5f, -14.0f));
		}

		TEST_METHOD(Tuple_MultiplyWithFraction)
		{
			rt::Tuple t1(1, -2, 3, -4);
			rt::Tuple t2 = t1 * 0.5f;
			Assert::IsTrue(t2 == rt::Tuple(0.5f, -1.0f, 1.5f, -2.0f));
		}

		TEST_METHOD(Tuple_DivideByScalar)
		{
			rt::Tuple t1(1, -2, 3, -4);
			rt::Tuple t2 = t1 / 2;
			Assert::IsTrue(t2 == rt::Tuple(0.5f, -1.0f, 1.5f, -2.0f));
		}

		TEST_METHOD(Vector_Magnitude)
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

		TEST_METHOD(Vector_Normalization)
		{
			rt::Vector v1(4, 0, 0);

			rt::Tuple r1 = v1.normalize();
			Assert::IsTrue(r1 == rt::Tuple(1, 0, 0, 0));

			rt::Vector r2 = v1.normalize();
			Assert::IsTrue(r2 == rt::Vector(1, 0, 0));

			rt::Vector v2(1, 2, 3);
			rt::Vector r3 = v2.normalize();
			Assert::AreEqual(r3.x(), 1.0f/sqrt(14.0f));
			Assert::AreEqual(r3.y(), 2.0f/sqrt(14.0f));
			Assert::AreEqual(r3.z(), 3.0f/sqrt(14.0f));
		}

		TEST_METHOD(Vector_MagnitudeOfNormalizedVector)
		{
			rt::Vector v1(4, 0, 0);
			rt::Vector r1 = v1.normalize();
			Assert::AreEqual(r1.magnitude(), 1.0f);
		}

		TEST_METHOD(Vector_DotProduct) 
		{
			rt::Vector v1(1, 2, 3);
			rt::Vector v2(2, 3, 4);
			Assert::AreEqual(v1.dot(v2), 20.0f);
		}		
		
		TEST_METHOD(Vector_CrossProduct) 
		{
			rt::Vector v1(1, 2, 3);
			rt::Vector v2(2, 3, 4);

			rt::Vector r1 = v1.cross(v2);
			Assert::IsTrue(r1 == rt::Vector(-1, 2, -1));

			rt::Vector r2 = v2.cross(v1);
			Assert::IsTrue(r2 == rt::Vector(1, -2, 1));
		}

		TEST_METHOD(Color_Assign)
		{
			rt::Color c(-0.5f, 0.4f, 1.7f);
			Assert::AreEqual(c.r(), -0.5f);
			Assert::AreEqual(c.g(), 0.4f);
			Assert::AreEqual(c.b(), 1.7f);
		}

		TEST_METHOD(Color_Add)
		{
			rt::Color c1(0.9f, 0.6f, 0.75f);
			rt::Color c2(0.7f, 0.1f, 0.25f);
			Assert::IsTrue(c1 + c2 == rt::Color(1.6f, 0.7f, 1.0f));
		}

		TEST_METHOD(Color_Substract)
		{
			rt::Color c1(0.9f, 0.6f, 0.75f);
			rt::Color c2(0.7f, 0.1f, 0.25f);
			Assert::IsTrue(c1 - c2 == rt::Color(0.2f, 0.5f, 0.5f));
		}

		TEST_METHOD(Color_MultiplyWithScalar)
		{
			rt::Color c(0.2f, 0.3f, 0.4f);
			Assert::IsTrue(c*2 == rt::Color(0.4f, 0.6f, 0.8f));
		}

		TEST_METHOD(Color_MultiplyWithColor)
		{
			rt::Color c1(1.0f, 0.2f, 0.4f);
			rt::Color c2(0.9f, 1.0f, 0.1f);
			Assert::IsTrue(c1*c2 == rt::Color(0.9f, 0.2f, 0.04f));
		}


	};
}
