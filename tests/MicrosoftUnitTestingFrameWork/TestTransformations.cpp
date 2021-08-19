#include "CppUnitTest.h"

#include "../../src/rtTransformations.hpp"
#include "../../src/rtMatrix.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestProject
{
	TEST_CLASS(TestTransformations)
	{
	public:

		TEST_METHOD(Translation_Multiply_By_Translation_Matrix)
		{
			rt::Matrix t = rt::translation(5, -3, 2);
			rt::Point p(-3, 4, 5);
			Assert::IsTrue(t * p == rt::Point(2, 1, 7));
		}

		TEST_METHOD(Translation_Multiply_By_Inverse_Of_Translation_Matrix)
		{
			rt::Matrix t = rt::translation(5, -3, 2);
			auto t_inv = t.inverse().value();
			rt::Point p(-3, 4, 5);
			Assert::IsTrue(t_inv * p == rt::Point(-8, 7, 3));
		}

		TEST_METHOD(Translation_Does_Not_Affect_Vectors)
		{
			rt::Matrix t = rt::translation(5, -3, 2);
			rt::Vector v(-3, 4, 5);
			Assert::IsTrue(t * v == v);
		}
	};
}