#include "CppUnitTest.h"

#include "../../src/rtMain.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestProject
{
	TEST_CLASS(TestLights)
	{
	public:

		TEST_METHOD(A_point_light_has_a_position_and_intensity)
		{
			rt::Color intensity = rt::Color(1, 1, 1);
			rt::Point position = rt::Point(0, 0, 0);
			auto light = rt::PointLight(position, intensity);
			Assert::IsTrue(light.position() == position);
			Assert::IsTrue(light.intensity() == intensity);
		}
	
	};
}