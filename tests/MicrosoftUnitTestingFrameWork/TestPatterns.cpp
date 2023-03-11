#include "CppUnitTest.h"

#include "../../src/rtMain.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestProject
{
	TEST_CLASS(TestPatterns)
	{
	public:

		TEST_METHOD(Create_a_striped_pattern)
		{
			rt::StripedPattern p = rt::StripedPattern(rt::WHITE, rt::BLACK);
			Assert::IsTrue(p.a == rt::WHITE);
			Assert::IsTrue(p.b == rt::BLACK);
		}

		
		TEST_METHOD(A_stripe_pattern_is_constant_in_Y)
		{
			rt::StripedPattern p = rt::StripedPattern(rt::WHITE, rt::BLACK);
			Assert::IsTrue(p.stripe_at(rt::Point(0, 0, 0)) == rt::WHITE);
			Assert::IsTrue(p.stripe_at(rt::Point(0, 1, 0)) == rt::WHITE);
			Assert::IsTrue(p.stripe_at(rt::Point(0, 2, 0)) == rt::WHITE);
		}

		TEST_METHOD(A_stripe_pattern_is_constant_in_Z)
		{
			rt::StripedPattern p = rt::StripedPattern(rt::WHITE, rt::BLACK);
			Assert::IsTrue(p.stripe_at(rt::Point(0, 0, 0)) == rt::WHITE);
			Assert::IsTrue(p.stripe_at(rt::Point(0, 0, 1)) == rt::WHITE);
			Assert::IsTrue(p.stripe_at(rt::Point(0, 0, 2)) == rt::WHITE);
		}

		TEST_METHOD(A_stripe_pattern_alternates_in_X)
		{
			rt::StripedPattern p = rt::StripedPattern(rt::WHITE, rt::BLACK);
			Assert::IsTrue(p.stripe_at(rt::Point(0, 0, 0)) == rt::WHITE);
			Assert::IsTrue(p.stripe_at(rt::Point(0.9f, 0, 0)) == rt::WHITE);
			Assert::IsTrue(p.stripe_at(rt::Point(1, 0, 0)) == rt::BLACK);
			Assert::IsTrue(p.stripe_at(rt::Point(-0.1f, 0, 0)) == rt::BLACK);
			Assert::IsTrue(p.stripe_at(rt::Point(-1, 0, 0)) == rt::BLACK);
			Assert::IsTrue(p.stripe_at(rt::Point(-1.1f, 0, 0)) == rt::WHITE);
		}
		
	};
}