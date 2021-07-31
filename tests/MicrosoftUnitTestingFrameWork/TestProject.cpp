#include "pch.h"
#include "CppUnitTest.h"

#include "../../src/rtTuple.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestProject
{
	TEST_CLASS(TestTuple)
	{
	public:
		
		TEST_METHOD(EmptyTupleReturnsZero)
		{
			rt::Tuple a;
			Assert::AreEqual(a.x, 0.0f);
			Assert::AreEqual(a.y, 0.0f);
			Assert::AreEqual(a.z, 0.0f);
			Assert::AreEqual(a.w, 0.0f);
		}

		TEST_METHOD(TupleWithW1IsPoint)
		{
			rt::Tuple a(4.3f, -4.2f, 3.1f, 1.0f);
			Assert::AreEqual(a.x, 4.3f);
			Assert::AreEqual(a.y, -4.2f);
			Assert::AreEqual(a.z, 3.1f);
			Assert::AreEqual(a.w, 1.0f);
			Assert::AreEqual(a.isPoint(), true);
		}

		TEST_METHOD(PointCreateTuplesWithW1)
		{
			rt::Point p(4, -4, 3);
			rt::Tuple t(4, -4, 3, 1);
			Assert::AreEqual(p.x, t.x);
			Assert::AreEqual(p.y, t.y);
			Assert::AreEqual(p.z, t.z);
			Assert::AreEqual(p.w, t.w);
			Assert::AreEqual(p.isPoint(), true);
		}		
		
		TEST_METHOD(VectorCreateTuplesWithW0)
		{
			rt::Vector v(4, -4, 3);
			rt::Tuple t(4, -4, 3, 0);
			Assert::AreEqual(v.x, t.x);
			Assert::AreEqual(v.y, t.y);
			Assert::AreEqual(v.z, t.z);
			Assert::AreEqual(v.w, t.w);
			Assert::AreEqual(v.isVector(), true);
		}

		TEST_METHOD(AddTwoTuples)
		{
			rt::Tuple a1(3, -2, 5, 1);
			rt::Tuple a2(-2, 3, 1, 0);
			rt::Tuple a3 = a1 + a2;
			Assert::AreEqual(a3.x, 1.0f);
			Assert::AreEqual(a3.y, 1.0f);
			Assert::AreEqual(a3.z, 6.0f);
			Assert::AreEqual(a3.w, 1.0f);
		}		
		
		TEST_METHOD(SubtractTwoPoints)
		{
			rt::Point p1(3, 2, 1);
			rt::Point p2(5, 6, 7);
			rt::Tuple t1 = p1 - p2;
			Assert::AreEqual(t1.x, -2.0f);
			Assert::AreEqual(t1.y, -4.0f);
			Assert::AreEqual(t1.z, -6.0f);
			Assert::AreEqual(t1.isVector(), true);
		}
		
		TEST_METHOD(SubtractVectorFromPoint)
		{
			rt::Point p1(3, 2, 1);
			rt::Vector v1(5, 6, 7);
			rt::Tuple t1 = p1 - v1;
			Assert::AreEqual(t1.x, -2.0f);
			Assert::AreEqual(t1.y, -4.0f);
			Assert::AreEqual(t1.z, -6.0f);
			Assert::AreEqual(t1.isPoint(), true);
		}
		
		TEST_METHOD(SubtractTwoVectors)
		{
			rt::Vector v1(3, 2, 1);
			rt::Vector v2(5, 6, 7);
			rt::Tuple t1 = v1 - v2;
			Assert::AreEqual(t1.x, -2.0f);
			Assert::AreEqual(t1.y, -4.0f);
			Assert::AreEqual(t1.z, -6.0f);
			Assert::AreEqual(t1.isVector(), true);
		}

		TEST_METHOD(SubtractVectorFromZeroVector)
		{
			rt::Vector zero(0, 0, 0);
			rt::Vector v1(1, -2, 3);
			rt::Tuple t1 = zero - v1;
			Assert::AreEqual(t1.x, -1.0f);
			Assert::AreEqual(t1.y, 2.0f);
			Assert::AreEqual(t1.z, -3.0f);
			Assert::AreEqual(t1.isVector(), true);
		}

		TEST_METHOD(NegateTuple)
		{
			rt::Tuple t1(1, -2, 3, -4);
			rt::Tuple t2 = -t1;
			Assert::AreEqual(t2.x, -1.0f);
			Assert::AreEqual(t2.y, 2.0f);
			Assert::AreEqual(t2.z, -3.0f);
			Assert::AreEqual(t2.w, 4.0f);
		}

		TEST_METHOD(MultiplyTupleWithScalar)
		{
			rt::Tuple t1(1, -2, 3, -4);
			rt::Tuple t2 = t1 * 3.5f;
			Assert::AreEqual(t2.x, 3.5f);
			Assert::AreEqual(t2.y, -7.0f);
			Assert::AreEqual(t2.z, 10.5f);
			Assert::AreEqual(t2.w, -14.0f);
		}

		TEST_METHOD(MultiplyTupleWithFraction)
		{
			rt::Tuple t1(1, -2, 3, -4);
			rt::Tuple t2 = t1 * 0.5f;
			Assert::AreEqual(t2.x, 0.5f);
			Assert::AreEqual(t2.y, -1.0f);
			Assert::AreEqual(t2.z, 1.5f);
			Assert::AreEqual(t2.w, -2.0f);
		}

		TEST_METHOD(DivideTupleByScalar)
		{
			rt::Tuple t1(1, -2, 3, -4);
			rt::Tuple t2 = t1 / 2;
			Assert::AreEqual(t2.x, 0.5f);
			Assert::AreEqual(t2.y, -1.0f);
			Assert::AreEqual(t2.z, 1.5f);
			Assert::AreEqual(t2.w, -2.0f);
		}

		TEST_METHOD(VectorMagnitude)
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

		TEST_METHOD(VectorNormalization)
		{
			rt::Vector v1(4, 0, 0);

			rt::Tuple r1 = v1.normalize();
			Assert::AreEqual(r1.x, 1.0f);
			Assert::AreEqual(r1.y, 0.0f);
			Assert::AreEqual(r1.z, 0.0f);

			rt::Vector r2 = v1.normalize();
			Assert::AreEqual(r2.x, 1.0f);
			Assert::AreEqual(r2.y, 0.0f);
			Assert::AreEqual(r2.z, 0.0f);

			rt::Vector v2(1, 2, 3);
			rt::Vector r3 = v2.normalize();
			Assert::AreEqual(r3.x, 1.0f/sqrt(14.0f));
			Assert::AreEqual(r3.y, 2.0f/sqrt(14.0f));
			Assert::AreEqual(r3.z, 3.0f/sqrt(14.0f));
		}

		TEST_METHOD(MagnitudeOfNormalizedVector)
		{
			rt::Vector v1(4, 0, 0);
			rt::Vector r1 = v1.normalize();
			Assert::AreEqual(r1.magnitude(), 1.0f);
		}

		TEST_METHOD(DotProduct) 
		{
			rt::Vector v1(1, 2, 3);
			rt::Vector v2(2, 3, 4);
			Assert::AreEqual(v1.dot(v2), 20.0f);

		}		
		
		TEST_METHOD(CrossProduct) 
		{
			rt::Vector v1(1, 2, 3);
			rt::Vector v2(2, 3, 4);

			rt::Vector r1 = v1.cross(v2);
			Assert::AreEqual(r1.x, -1.0f);
			Assert::AreEqual(r1.y, 2.0f);
			Assert::AreEqual(r1.z, -1.0f);

			rt::Vector r2 = v2.cross(v1);
			Assert::AreEqual(r2.x, 1.0f);
			Assert::AreEqual(r2.y, -2.0f);
			Assert::AreEqual(r2.z, 1.0f);
		}

	};
}
