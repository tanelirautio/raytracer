#include "pch.h"
#include "CppUnitTest.h"

#include "../../src/rtMatrix.hpp"
#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestProject
{
	TEST_CLASS(TestMatrix)
	{
	public:

		TEST_METHOD(Matrix_Create)
		{

			std::vector<float> values = { 1.0f,  2.0f,  3.0f,  4.0f,
										  5.5f,  6.5f,  7.5f,  8.5f,
										  9.0f,  10.f,  11.f,  12.f,
										  13.5f, 14.5f, 15.5f, 16.5f };
			rt::Matrix m(4, 4, values);

			Assert::AreEqual(m.at(0, 0), 1.0f);
			Assert::AreEqual(m.at(0, 3), 4.0f);
			Assert::AreEqual(m.at(1, 0), 5.5f);
			Assert::AreEqual(m.at(1, 2), 7.5f);
			Assert::AreEqual(m.at(2, 2), 11.0f);
			Assert::AreEqual(m.at(3, 0), 13.5f);
			Assert::AreEqual(m.at(3, 2), 15.5f);
		}
	};
}