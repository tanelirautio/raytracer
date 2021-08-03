#include "pch.h"
#include "CppUnitTest.h"

#include "../../src/rtCanvas.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestProject
{
	TEST_CLASS(TestCanvas)
	{
	public:

		TEST_METHOD(Canvas_Create)
		{
			rt::Canvas c(10, 20);
			Assert::AreEqual(c.get_width(), 10);
			Assert::AreEqual(c.get_height(), 20);
			for (int y = 0; y < c.get_height(); y++) {
				for (int x = 0; x < c.get_width(); x++) {
					Assert::IsTrue(c.pixel_at(x, y) == rt::Color(0, 0, 0));
				}
			}
		}

		TEST_METHOD(Canvas_WritePixels)
		{
			rt::Canvas c(10, 20);
			rt::Color red(1, 0, 0);
			c.write_pixel(2, 3, red);
			Assert::IsTrue(c.pixel_at(2, 3) == rt::Color(1, 0, 0));

			auto p = c.pixel_at(10, 20);
		}
	};
}
