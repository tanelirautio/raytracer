#include "pch.h"
#include "CppUnitTest.h"

#include "../RayTracer/rtTuple.hpp"

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
		}

		TEST_METHOD(PointCreateTuplesWithW1)
		{
			rt::Point p(4, -4, 3);
			rt::Tuple t(4, -4, 3, 1);
			Assert::AreEqual(p.x, t.x);
			Assert::AreEqual(p.y, t.y);
			Assert::AreEqual(p.z, t.z);
			Assert::AreEqual(p.w, t.w);
		}		
		
		TEST_METHOD(VectorCreateTuplesWithW0)
		{
			rt::Vector v(4, -4, 3);
			rt::Tuple t(4, -4, 3, 0);
			Assert::AreEqual(v.x, t.x);
			Assert::AreEqual(v.y, t.y);
			Assert::AreEqual(v.z, t.z);
			Assert::AreEqual(v.w, t.w);
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
	};
}
