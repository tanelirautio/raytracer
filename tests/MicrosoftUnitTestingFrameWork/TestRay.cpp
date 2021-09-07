#include "CppUnitTest.h"

#include "../../src/rtMain.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestProject
{
	TEST_CLASS(TestRay)
	{
	public:
		TEST_METHOD(Creating_And_Querying)
		{
			rt::Point origin(1, 2, 3);
			rt::Vector direction(4, 5, 6);
			rt::Ray ray(origin, direction);

			Assert::IsTrue(ray.origin() == rt::Point(1, 2, 3));
			Assert::IsTrue(ray.direction() == rt::Vector(4, 5, 6));
		}

		TEST_METHOD(Compute_Point_From_Distance)
		{
			rt::Point origin(2, 3, 4);
			rt::Vector direction(1, 0, 0);
			rt::Ray ray(origin, direction);

			Assert::IsTrue(ray.position(0) == rt::Point(2, 3, 4));
			Assert::IsTrue(ray.position(1) == rt::Point(3, 3, 4));
			Assert::IsTrue(ray.position(-1) == rt::Point(1, 3, 4));
			Assert::IsTrue(ray.position(2.5f) == rt::Point(4.5f, 3, 4));
		}

		TEST_METHOD(Translating_A_Ray)
		{
			rt::Ray r({ 1,2,3 }, { 0,1,0 });
			rt::Matrix m = rt::translation(3, 4, 5);
			rt::Ray r2 = r.transform(m);

			Assert::IsTrue(r2.origin() == rt::Point(4, 6, 8));
			Assert::IsTrue(r2.direction() == rt::Vector(0, 1, 0));
		}
		TEST_METHOD(Scaling_A_Ray)
		{
			rt::Ray r({ 1,2,3 }, { 0,1,0 });
			rt::Matrix m = rt::scaling(2, 3, 4);
			rt::Ray r2 = r.transform(m);

			Assert::IsTrue(r2.origin() == rt::Point(2, 6, 12));
			Assert::IsTrue(r2.direction() == rt::Vector(0, 3, 0));
		}

	};
}