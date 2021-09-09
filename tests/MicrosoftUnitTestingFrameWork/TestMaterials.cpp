#include "CppUnitTest.h"

#include "../../src/rtMain.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestProject
{
	TEST_CLASS(TestMaterials)
	{
	public:

		TEST_METHOD(The_default_material)
		{
			rt::Material m;
			Assert::IsTrue(m.color() == rt::Color(1,1,1));
			Assert::IsTrue(m.ambient() == 0.1f);
			Assert::IsTrue(m.diffuse() == 0.9f);
			Assert::IsTrue(m.specular() == 0.9f);
			Assert::IsTrue(m.shininess() == 200.f);
		}

		TEST_METHOD(Lighting_with_the_eye_between_the_light_and_and_the_surface)
		{
			rt::Point position(0, 0, 0);
			rt::Material m;
			rt::Vector eyev = rt::Vector(0, 0, -1);
			rt::Vector normalv = rt::Vector(0, 0, -1);
			rt::PointLight light({ 0,0,-10 }, { 1,1,1 });
			rt::Color result = rt::lighting(m, light, position, eyev, normalv);
			Assert::IsTrue(result == rt::Color(1.9f,1.9f,1.9f));
		}

		TEST_METHOD(Lighting_with_the_eye_between_the_light_and_and_the_surface_Eye_offset_45_degrees)
		{
			rt::Point position(0, 0, 0);
			rt::Material m;
			rt::Vector eyev = rt::Vector(0, sqrt(2.f)/2.f, -sqrt(2.f)/2.f);
			rt::Vector normalv = rt::Vector(0, 0, -1);
			rt::PointLight light({ 0, 0, -10 }, { 1, 1, 1 });
			rt::Color result = rt::lighting(m, light, position, eyev, normalv);
			Assert::IsTrue(result == rt::Color(1.0f,1.0f,1.0f));
		}

		TEST_METHOD(Lighting_with_the_eye_opposite_surface_Light_offset_45_degrees)
		{
			rt::Point position(0, 0, 0);
			rt::Material m;
			rt::Vector eyev = rt::Vector(0, 0, -1); 
			rt::Vector normalv = rt::Vector(0, 0, -1);
			rt::PointLight light({ 0, 10, -10 }, { 1, 1, 1 });
			rt::Color result = rt::lighting(m, light, position, eyev, normalv);
			Assert::IsTrue(result == rt::Color(0.7364f, 0.7364f, 0.7364f));
		}

		TEST_METHOD(Lighting_with_the_eye_in_the_path_of_reflection_vector)
		{
			rt::Point position(0, 0, 0);
			rt::Material m;
			rt::Vector eyev = rt::Vector(0, -sqrt(2.f) / 2.f, -sqrt(2.f) / 2.f);
			rt::Vector normalv = rt::Vector(0, 0, -1);
			rt::PointLight light({ 0, 10, -10 }, { 1, 1, 1 });
			rt::Color result = rt::lighting(m, light, position, eyev, normalv);
			Assert::IsTrue(result == rt::Color(1.63638f, 1.63638f, 1.63638f));
		}

		TEST_METHOD(Lighting_with_the_light_behind_the_surface)
		{
			rt::Point position(0, 0, 0);
			rt::Material m;
			rt::Vector eyev = rt::Vector(0, 0, -1);
			rt::Vector normalv = rt::Vector(0, 0, -1);
			rt::PointLight light({ 0, 0, 10 }, { 1, 1, 1 });
			rt::Color result = rt::lighting(m, light, position, eyev, normalv);
			Assert::IsTrue(result == rt::Color(0.1f, 0.1f, 0.1f));
		}


	};
}