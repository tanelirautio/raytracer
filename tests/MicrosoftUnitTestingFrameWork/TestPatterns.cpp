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
			Assert::IsTrue(p.pattern_at(rt::Point(0, 0, 0)) == rt::WHITE);
			Assert::IsTrue(p.pattern_at(rt::Point(0, 1, 0)) == rt::WHITE);
			Assert::IsTrue(p.pattern_at(rt::Point(0, 2, 0)) == rt::WHITE);
		}

		TEST_METHOD(A_stripe_pattern_is_constant_in_Z)
		{
			rt::StripedPattern p = rt::StripedPattern(rt::WHITE, rt::BLACK);
			Assert::IsTrue(p.pattern_at(rt::Point(0, 0, 0)) == rt::WHITE);
			Assert::IsTrue(p.pattern_at(rt::Point(0, 0, 1)) == rt::WHITE);
			Assert::IsTrue(p.pattern_at(rt::Point(0, 0, 2)) == rt::WHITE);
		}

		TEST_METHOD(A_stripe_pattern_alternates_in_X)
		{
			rt::StripedPattern p = rt::StripedPattern(rt::WHITE, rt::BLACK);
			Assert::IsTrue(p.pattern_at(rt::Point(0, 0, 0)) == rt::WHITE);
			Assert::IsTrue(p.pattern_at(rt::Point(0.9f, 0, 0)) == rt::WHITE);
			Assert::IsTrue(p.pattern_at(rt::Point(1, 0, 0)) == rt::BLACK);
			Assert::IsTrue(p.pattern_at(rt::Point(-0.1f, 0, 0)) == rt::BLACK);
			Assert::IsTrue(p.pattern_at(rt::Point(-1, 0, 0)) == rt::BLACK);
			Assert::IsTrue(p.pattern_at(rt::Point(-1.1f, 0, 0)) == rt::WHITE);
		}
		
		TEST_METHOD(The_default_pattern_transformation) 
		{
			rt::TestPattern p = rt::TestPattern();
			Assert::IsTrue(p.transform() == rt::get_identity_matrix4());
		}

		TEST_METHOD(Assigning_a_transformation)
		{
			rt::TestPattern p = rt::TestPattern();
			p.transform() = rt::translation(1, 2, 3);
			Assert::IsTrue(p.transform() == rt::translation(1, 2, 3));
		}
		
		TEST_METHOD(Pattern_with_an_object_transformation)
		{
			rt::Sphere object = rt::Sphere();
			object.transform() = rt::scaling(2, 2, 2);
			rt::TestPattern pattern;
			rt::Color c = pattern.pattern_at_shape(object, { 2, 3, 4 });
			Assert::IsTrue(c == rt::Color(1, 1.5f, 2));
		}

		TEST_METHOD(Pattern_with_a_pattern_transformation)
		{
			rt::Sphere object = rt::Sphere();
			rt::TestPattern pattern;
			pattern.transform() = rt::scaling(2, 2, 2);
			rt::Color c = pattern.pattern_at_shape(object, { 2, 3, 4 });
			Assert::IsTrue(c == rt::Color(1, 1.5f, 2));
		}

		TEST_METHOD(Pattern_with_both_an_object_and_a_pattern_transformation)
		{
			rt::Sphere object = rt::Sphere();
			object.transform() = rt::scaling(2, 2, 2);
			rt::TestPattern pattern;
			pattern.transform() = rt::translation(0.5f, 1, 1.5f);

			rt::Color c = pattern.pattern_at_shape(object, { 2.5f, 3, 3.5f});
			Assert::IsTrue(c == rt::Color(0.75f, 0.5f, 0.25f));
		}

		TEST_METHOD(A_gradient_linearly_interpolates_between_colors)
		{
			rt::GradientPattern p(rt::WHITE, rt::BLACK);
			Assert::IsTrue(p.pattern_at({ 0,0,0 }) == rt::WHITE);
			Assert::IsTrue(p.pattern_at({ 0.25f,0,0 }) == rt::Color(0.75f, 0.75f, 0.75f));
			Assert::IsTrue(p.pattern_at({ 0.5f,0,0 }) == rt::Color(0.5f, 0.5f, 0.5f));
			Assert::IsTrue(p.pattern_at({ 0.75f,0,0 }) == rt::Color(0.25f, 0.25f, 0.25f));
		}

		TEST_METHOD(A_ring_should_extend_in_both_x_and_z)
		{
			rt::RingPattern p(rt::WHITE, rt::BLACK);
			Assert::IsTrue(p.pattern_at({ 0,0,0 }) == rt::WHITE);
			Assert::IsTrue(p.pattern_at({ 1,0,0 }) == rt::BLACK);
			Assert::IsTrue(p.pattern_at({ 0,0,1 }) == rt::BLACK);
			// 0.708f = just slightly more than sqrt(2)/2
			Assert::IsTrue(p.pattern_at({ 0.708f, 0, 0.708f }) == rt::BLACK);
		}
	};
}