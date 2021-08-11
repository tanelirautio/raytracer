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

		TEST_METHOD(Matrix_Create_4x4)
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

		TEST_METHOD(Matrix_Create_2x2)
		{
			std::vector<float> values = { -3,  5,  
										  1,  -2 };
			rt::Matrix m(2, 2, values);

			Assert::AreEqual(m.at(0, 0), -3.0f);
			Assert::AreEqual(m.at(0, 1), 5.0f);
			Assert::AreEqual(m.at(1, 0), 1.0f);
			Assert::AreEqual(m.at(1, 1), -2.0f);
		}

		TEST_METHOD(Matrix_Create_3x3)
		{
			std::vector<float> values = { -3,   5,   0,
										   1,  -2,  -7,
										   0,   1,   1 };
			rt::Matrix m(3, 3, values);

			Assert::AreEqual(m.at(0, 0), -3.0f);
			Assert::AreEqual(m.at(1, 1), -2.0f);
			Assert::AreEqual(m.at(2, 2), 1.0f);
		}		
		
		TEST_METHOD(Matrix_Equality_Identical_Matrices)
		{
			std::vector<float> values_A = { 1, 2, 3, 4,
											5, 6, 7, 8,
											9, 8, 7, 6,
											5, 4, 3, 2};			
			
			std::vector<float> values_B = { 1, 2, 3, 4,
											5, 6, 7, 8,
											9, 8, 7, 6,
											5, 4, 3, 2};
			
			
			rt::Matrix A(4, 4, values_A);
			rt::Matrix B(4, 4, values_B);

			Assert::IsTrue(A == B);
		}

		TEST_METHOD(Matrix_Equality_Different_Matrices)
		{
			std::vector<float> values_A = { 1, 2, 3, 4,
											5, 6, 7, 8,
											9, 8, 7, 6,
											5, 4, 3, 2};			
			
			std::vector<float> values_B = { 2, 3, 4, 5,
											6, 7, 8, 9,
											8, 7, 6, 5,
											4, 3, 2, 1};
			
			
			rt::Matrix A(4, 4, values_A);
			rt::Matrix B(4, 4, values_B);

			Assert::IsTrue(A != B);
		}


	};
}