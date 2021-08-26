#include "CppUnitTest.h"

#include "../../src/rtRay.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestProject
{
	TEST_CLASS(TestRay)
	{
	public:
		TEST_METHOD(Ray_Creating_And_Querying)
		{
			rt::Point origin(1, 2, 3);
			rt::Vector direction(4, 5, 6);
			rt::Ray ray(origin, direction);

			Assert::IsTrue(ray.origin() == rt::Point(1, 2, 3));
			Assert::IsTrue(ray.direction() == rt::Vector(4, 5, 6));
		}

		TEST_METHOD(Ray_Compute_Point_From_Distance)
		{
			rt::Point origin(2, 3, 4);
			rt::Vector direction(1, 0, 0);
			rt::Ray ray(origin, direction);

			Assert::IsTrue(ray.position(0) == rt::Point(2, 3, 4));
			Assert::IsTrue(ray.position(1) == rt::Point(3, 3, 4));
			Assert::IsTrue(ray.position(-1) == rt::Point(1, 3, 4));
			Assert::IsTrue(ray.position(2.5f) == rt::Point(4.5f, 3, 4));
		}


	};
}