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

		TEST_METHOD(Matrix_Multiplication)
		{
			std::vector<float> values_A = { 1, 2, 3, 4,
											5, 6, 7, 8,
											9, 8, 7, 6,
											5, 4, 3, 2 };

			std::vector<float> values_B = { -2, 1, 2, 3,
											3, 2, 1, -1,
											4, 3, 6, 5,
											1, 2, 7, 8 };

			std::vector<float> values_C = { 20, 22, 50, 48,
											44, 54, 114, 108,
											40, 58, 110, 102,
											16, 26, 46, 42 };

			rt::Matrix A(4, 4, values_A);
			rt::Matrix B(4, 4, values_B);
			rt::Matrix C(4, 4, values_C);
			Assert::IsTrue(A * B == C);
		}

		TEST_METHOD(Matrix_Multiplied_With_Tuple)
		{
			std::vector<float> values_A = { 1, 2, 3, 4,
											2, 4, 4, 2,
											8, 6, 4, 1,
											0, 0, 0, 1 };

			rt::Matrix A(4, 4, values_A);
			rt::Tuple B(1, 2, 3, 1);
			rt::Tuple C(18, 24, 33, 1);

			Assert::IsTrue(A * B == C);
		}

		TEST_METHOD(Matrix_Multiplication_With_Identity_Matrix)
		{
			std::vector<float> values_A = { 0, 1, 2, 4,
											1, 2, 4, 8,
											2, 4, 8, 16,
											4, 8, 16, 32 };

			rt::Matrix A(4, 4, values_A);
			rt::Matrix B = rt::get_identity_matrix(4);
			Assert::IsTrue(A * B == A);
		}

		TEST_METHOD(Matrix_Identity_Matrix_Multiplied_With_Tuple)
		{
			rt::Matrix A = rt::get_identity_matrix(4);
			rt::Tuple B(1, 2, 3, 4);
			Assert::IsTrue(A * B == B);
		}
		
		TEST_METHOD(Matrix_Transpose_Matrix)
		{
			std::vector<float> values_A = { 0, 9, 3, 0,
											9, 8, 0, 8,
											1, 8, 5, 3,
											0, 0, 5, 8 };

			std::vector<float> values_B = { 0, 9, 1, 0,
											9, 8, 8, 0,
											3, 0, 5, 5,
											0, 8, 3, 8 };

			rt::Matrix A(4, 4, values_A);
			rt::Matrix B(4, 4, values_B);
			Assert::IsTrue(A.transpose() == B);
		}

		TEST_METHOD(Matrix_Transpose_Identity_Matrix)
		{
			std::vector<float> values_I = { 1, 0, 0, 0,
											0, 1, 0, 0,
											0, 0, 1, 0,
											0, 0, 0, 1 };

			rt::Matrix A = rt::get_identity_matrix(4);
			rt::Matrix I(4, 4, values_I);
			Assert::IsTrue(A.transpose() == rt::get_identity_matrix(4));
			Assert::IsTrue(A.transpose() == I);
		}

		TEST_METHOD(Matrix_2x2_Determinant)
		{
			std::vector<float> values_A = { 1, 5,
											-3, 2 };
			rt::Matrix A(2, 2, values_A);
			Assert::IsTrue(A.determinant() == 17);
		}

		TEST_METHOD(Matrix_3x3_Submatrix)
		{
			std::vector<float> values_A = { 1, 5, 0,
											-3, 2, 7,
											0, 6, -3};
			std::vector<float> values_B = { -3, 2,
											0, 6 };
			rt::Matrix A(3, 3, values_A);
			rt::Matrix B(2, 2, values_B);

			Assert::IsTrue(A.submatrix(0,2) == B);
		}

		TEST_METHOD(Matrix_4x4_Submatrix)
		{
			std::vector<float> values_A = { -6, 1, 1, 6,
											-8, 5, 8, 6,
											-1, 0, 8, 2,
											-7, 1, -1, 1 };
			std::vector<float> values_B = { -6, 1, 6,
											-8, 8, 6,
											-7, -1, 1 };
			rt::Matrix A(4, 4, values_A);
			rt::Matrix B(3, 3, values_B);

			Assert::IsTrue(A.submatrix(2,1) == B);
		}		
		
		TEST_METHOD(Matrix_Calculate_Minor_Of_3x3_Matrix)
		{
			std::vector<float> values_A = { 3, 5, 0,
											2, -1, -7,
											6, -1, 5 };
			rt::Matrix A(3, 3, values_A);
			rt::Matrix B = A.submatrix(1, 0);

			Assert::IsTrue(B.determinant() == 25);
			Assert::IsTrue(A.minor(1,0) == 25);
		}

		TEST_METHOD(Matrix_Compute_Cofactor)
		{
			std::vector<float> values_A = { 3, 5, 0,
											2, -1, -7,
											6, -1, 5 };
			rt::Matrix A(3, 3, values_A);

			Assert::IsTrue(A.minor(0,0) == -12);
			Assert::IsTrue(A.cofactor(0,0) == -12);
			Assert::IsTrue(A.minor(1,0) == 25);
			Assert::IsTrue(A.cofactor(1,0) == -25);
		}

		TEST_METHOD(Matrix_3x3_Determinant)
		{
			std::vector<float> values_A = { 1, 2, 6,
											-5, 8, -4,
											2, 6, 4 };
			rt::Matrix A(3, 3, values_A);

			Assert::IsTrue(A.cofactor(0,0) == 56);
			Assert::IsTrue(A.cofactor(0,1) == 12);
			Assert::IsTrue(A.cofactor(0,2) == -46);
			Assert::IsTrue(A.determinant() == -196);
		}

		TEST_METHOD(Matrix_4x4_Determinant)
		{
			std::vector<float> values_A = { -2, -8, 3, 5,
											-3, 1, 7, 3,
											1, 2, -9, 6,
											-6, 7, 7, -9 };
			rt::Matrix A(4, 4, values_A);

			Assert::IsTrue(A.cofactor(0,0) == 690);
			Assert::IsTrue(A.cofactor(0,1) == 447);
			Assert::IsTrue(A.cofactor(0,2) == 210);
			Assert::IsTrue(A.cofactor(0,3) == 51);
			Assert::IsTrue(A.determinant() == -4071);
		}
		
		TEST_METHOD(Matrix_Invert_Invertible_Matrix)
		{
			std::vector<float> values_A = { 6, 4, 4, 4,
											5, 5, 7, 6,
											4, -9, 3, -7,
											9, 1, 7, -6 };
			rt::Matrix A(4, 4, values_A);

			Assert::IsTrue(A.determinant() == -2120);
			auto B = A.inverse();
			if (!B) {
				Assert::Fail();
			}
		}
		
		TEST_METHOD(Matrix_Invert_Non_Invertible_Matrix)
		{
			std::vector<float> values_A = { -4, 2, -2, -3,
											9, 6, 2, 6,
											0, -5, 1, -5,
											0, 0, 0, 0 };
			rt::Matrix A(4, 4, values_A);

			Assert::IsTrue(A.determinant() == 0);
			auto B = A.inverse();
			if (B) {
				Assert::Fail();
			}
		}


	};
}