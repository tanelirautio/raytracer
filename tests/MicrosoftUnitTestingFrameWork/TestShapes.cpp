#include "CppUnitTest.h"

#include "../../src/rtMain.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestProject
{
	TEST_CLASS(TestShape)
	{
	public:
		TEST_METHOD(The_default_transformation)
		{
			rt::TestShape s;
			Assert::IsTrue(s.transform() == rt::get_identity_matrix4());
		}

		TEST_METHOD(Assigning_a_transformation)
		{
			rt::TestShape s;
			s.transform() = rt::translation(2, 3, 4);
			Assert::IsTrue(s.transform() == rt::translation(2, 3, 4));
		}

		TEST_METHOD(The_default_material)
		{
			rt::TestShape s;
			auto m = s.material();
			Assert::IsTrue(m == rt::Material());
		}

		TEST_METHOD(Assigning_a_material)
		{
			rt::TestShape s;
			auto m = s.material();
			m.ambient = 1;
			s.material() = m;
			Assert::IsTrue(s.material() == m);
		}


	};
}