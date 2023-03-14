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
			Assert::IsTrue(p.a() == rt::WHITE);
			Assert::IsTrue(p.b() == rt::BLACK);
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
		
		TEST_METHOD(Stripes_with_an_object_transformation)
		{
			rt::Sphere object = rt::Sphere();
			object.transform() = rt::scaling(2, 2, 2);
			rt::StripedPattern pattern(rt::WHITE, rt::BLACK);
			rt::Color c = pattern.stripe_at_object(object, { 1.5f, 0, 0 });
			Assert::IsTrue(c == rt::WHITE);
		}

		TEST_METHOD(Stripes_with_a_pattern_transformation)
		{
			rt::Sphere object = rt::Sphere();
			rt::StripedPattern pattern(rt::WHITE, rt::BLACK);
			pattern.set_transform(rt::scaling(2, 2, 2));
			rt::Color c = pattern.stripe_at_object(object, { 1.5f, 0, 0 });
			Assert::IsTrue(c == rt::WHITE);
		}

		TEST_METHOD(Striped_with_both_an_object_and_a_pattern_transformation)
		{
			rt::Sphere object = rt::Sphere();
			object.transform() = rt::scaling(2, 2, 2);
			rt::StripedPattern pattern(rt::WHITE, rt::BLACK);
			pattern.set_transform(rt::translation(0.5f, 0, 0));
			rt::Color c = pattern.stripe_at_object(object, { 2.5f, 0, 0 });
			Assert::IsTrue(c == rt::WHITE);
		}

	};
}