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
		}

		std::vector<std::string> split_string_by_newline(const std::string& str)
		{
			auto result = std::vector<std::string>{};
			auto ss = std::stringstream{ str };

			for (std::string line; std::getline(ss, line, '\n');)
				result.push_back(line);

			return result;
		}

		TEST_METHOD(Canvas_ConstructPPMHeader) 
		{
			rt::Canvas c(5, 3);
			auto data = c.canvas_to_ppm();
			auto lines = split_string_by_newline(data);

			Assert::AreEqual(lines[0].c_str(), "P3");
			Assert::AreEqual(lines[1].c_str(), "5 3");
			Assert::AreEqual(lines[2].c_str(), "255");
		}

		TEST_METHOD(Canvas_ConstructPPMPixelData) 
		{
			rt::Canvas c(5, 3);
			rt::Color c1(1.5f, 0, 0);
			rt::Color c2(0, 0.5f, 0);
			rt::Color c3(-0.5f, 0, 1);

			c.write_pixel(0, 0, c1);
			c.write_pixel(2, 1, c2);
			c.write_pixel(4, 2, c3);

			auto data = c.canvas_to_ppm();
			auto lines = split_string_by_newline(data);

			Assert::AreEqual(lines[3].c_str(), "255 0 0 0 0 0 0 0 0 0 0 0 0 0 0");
			Assert::AreEqual(lines[4].c_str(), "0 0 0 0 0 0 0 128 0 0 0 0 0 0 0");
			Assert::AreEqual(lines[5].c_str(), "0 0 0 0 0 0 0 0 0 0 0 0 0 0 255");
		}		
		
		TEST_METHOD(Canvas_SplittingLongLinesInPPMFiles) 
		{
			rt::Canvas c(10, 2);
			rt::Color c1(1.0f, 0.8f, 0.6f);

			for (int y = 0; y < c.get_height(); y++) {
				for (int x = 0; x < c.get_width(); x++) {
					c.write_pixel(x, y, c1);
				}
			}

			auto data = c.canvas_to_ppm();
			auto lines = split_string_by_newline(data);

			Assert::AreEqual(lines[3].c_str(), "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204");
			Assert::AreEqual(lines[4].c_str(), "153 255 204 153 255 204 153 255 204 153 255 204 153");
			Assert::AreEqual(lines[5].c_str(), "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204");
			Assert::AreEqual(lines[6].c_str(), "153 255 204 153 255 204 153 255 204 153 255 204 153");	
		}

		TEST_METHOD(Canvas_FilesAreTerminatedWithNewline)
		{
			rt::Canvas c(5, 3);
			auto data = c.canvas_to_ppm();

			Assert::AreEqual(data.back(), '\n');
		}


	};
}
