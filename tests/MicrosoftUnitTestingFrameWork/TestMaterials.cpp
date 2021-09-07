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
	};
}