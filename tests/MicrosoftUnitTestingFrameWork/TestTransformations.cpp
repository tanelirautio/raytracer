#include "CppUnitTest.h"

#include "../../src/rtMain.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestProject
{
	TEST_CLASS(TestTransformations)
	{
	public:
		TEST_METHOD(Translation_Multiply_By_Translation_Matrix)
		{
			rt::Matrix t = rt::translation(5, -3, 2);
			rt::Point p(-3, 4, 5);
			Assert::IsTrue(t * p == rt::Point(2, 1, 7));
		}

		TEST_METHOD(Translation_Multiply_By_Inverse_Of_Translation_Matrix)
		{
			rt::Matrix t = rt::translation(5, -3, 2);
			auto t_inv = t.inverse().value();
			rt::Point p(-3, 4, 5);
			Assert::IsTrue(t_inv * p == rt::Point(-8, 7, 3));
		}

		TEST_METHOD(Translation_Does_Not_Affect_Vectors)
		{
			rt::Matrix t = rt::translation(5, -3, 2);
			rt::Vector v(-3, 4, 5);
			Assert::IsTrue(t * v == v);
		}		
		
		TEST_METHOD(Scaling_Matrix_Applied_To_Point)
		{
			rt::Matrix s = rt::scaling(2, 3, 4);
			rt::Point p(-4, 6, 8);
			Assert::IsTrue(s * p == rt::Point(-8, 18, 32));
		}

		TEST_METHOD(Scaling_Matrix_Applied_To_Vector)
		{
			rt::Matrix s = rt::scaling(2, 3, 4);
			rt::Vector v(-4, 6, 8);
			Assert::IsTrue(s * v == rt::Vector(-8, 18, 32));
		}

		TEST_METHOD(Scaling_Multiply_By_The_Inverse_Of_Scaling_Matrix)
		{
			rt::Matrix s = rt::scaling(2, 3, 4);
			rt::Matrix s_inv = s.inverse().value();
			rt::Vector v(-4, 6, 8);
			Assert::IsTrue(s_inv * v == rt::Vector(-2, 2, 2));
		}

		TEST_METHOD(Scaling_Reflection_Is_Scaling_By_A_Negative_Value)
		{
			rt::Matrix s = rt::scaling(-1, 1, 1);
			rt::Point p(2, 3, 4);
			Assert::IsTrue(s * p == rt::Point(-2, 3, 4));
		}

		TEST_METHOD(Rotation_Rotate_A_Point_Around_X_Axis)
		{
			rt::Point p(0, 1, 0);
			rt::Matrix half_quarter = rt::rotation_x((f32)M_PI / 4.f);
			rt::Matrix full_quarter = rt::rotation_x((f32)M_PI / 2.f);
			
			Assert::IsTrue(half_quarter * p == rt::Point(0, sqrt(2.f)/2.f, sqrt(2.f)/2.f));
			Assert::IsTrue(full_quarter * p == rt::Point(0, 0, 1));	
		}

		TEST_METHOD(Rotation_The_Inverse_Of_An_X_Rotation_Rotates_In_The_Opposite_Direction)
		{
			rt::Point p(0, 1, 0);
			rt::Matrix half_quarter = rt::rotation_x((f32)M_PI / 4.f);
			auto inv = half_quarter.inverse().value();
			Assert::IsTrue(inv * p == rt::Point(0, sqrt(2.f)/2.f, -sqrt(2.f)/2.f));
		}

		TEST_METHOD(Rotation_Rotate_A_Point_Around_Y_Axis)
		{
			rt::Point p(0, 0, 1);
			rt::Matrix half_quarter = rt::rotation_y((f32)M_PI / 4.f);
			rt::Matrix full_quarter = rt::rotation_y((f32)M_PI / 2.f);

			Assert::IsTrue(half_quarter * p == rt::Point(sqrt(2.f)/2.f, 0, sqrt(2.f)/2.f));
			Assert::IsTrue(full_quarter * p == rt::Point(1, 0, 0));
		}

		TEST_METHOD(Rotation_Rotate_A_Point_Around_Z_Axis)
		{
			rt::Point p(0, 1, 0);
			rt::Matrix half_quarter = rt::rotation_z((f32)M_PI / 4.f);
			rt::Matrix full_quarter = rt::rotation_z((f32)M_PI / 2.f);
			
			Assert::IsTrue(half_quarter * p == rt::Point(-sqrt(2.f)/2.f, sqrt(2.f)/2.f, 0));
			Assert::IsTrue(full_quarter * p == rt::Point(-1, 0, 0));	
		}

		TEST_METHOD(Shearing_Transformation_Moves_X_In_Proportion_To_Y) 
		{
			rt::Matrix t = rt::shearing(1, 0, 0, 0, 0, 0);
			rt::Point p(2, 3, 4);
			Assert::IsTrue(t * p == rt::Point(5, 3, 4));
		}

		TEST_METHOD(Shearing_Transformation_Moves_X_In_Proportion_To_Z) 
		{
			rt::Matrix t = rt::shearing(0, 1, 0, 0, 0, 0);
			rt::Point p(2, 3, 4);
			Assert::IsTrue(t * p == rt::Point(6, 3, 4));
		}

		TEST_METHOD(Shearing_Transformation_Moves_Y_In_Proportion_To_X) 
		{
			rt::Matrix t = rt::shearing(0, 0, 1, 0, 0, 0);
			rt::Point p(2, 3, 4);
			Assert::IsTrue(t * p == rt::Point(2, 5, 4));
		}

		TEST_METHOD(Shearing_Transformation_Moves_Y_In_Proportion_To_Z) 
		{
			rt::Matrix t = rt::shearing(0, 0, 0, 1, 0, 0);
			rt::Point p(2, 3, 4);
			Assert::IsTrue(t * p == rt::Point(2, 7, 4));
		}

		TEST_METHOD(Shearing_Transformation_Moves_Z_In_Proportion_To_X) 
		{
			rt::Matrix t = rt::shearing(0, 0, 0, 0, 1, 0);
			rt::Point p(2, 3, 4);
			Assert::IsTrue(t * p == rt::Point(2, 3, 6));
		}

		TEST_METHOD(Shearing_Transformation_Moves_Z_In_Proportion_To_Y) 
		{
			rt::Matrix t = rt::shearing(0, 0, 0, 0, 0, 1);
			rt::Point p(2, 3, 4);
			Assert::IsTrue(t * p == rt::Point(2, 3, 7));
		}

		TEST_METHOD(Transformation_Individual_Transformations_Are_Applied_In_Sequence)
		{
			rt::Point p(1, 0, 1);
			auto a = rt::rotation_x((f32)M_PI / 2);
			auto b = rt::scaling(5, 5, 5);
			auto c = rt::translation(10, 5, 7);

			// rotation first
			auto p2 = a * p;
			Assert::IsTrue(p2 == rt::Point(1, -1, 0));

			// then scaling
			auto p3 = b * p2;
			Assert::IsTrue(p3 == rt::Point(5, -5, 0));

			// then translation
			auto p4 = c * p3;
			Assert::IsTrue(p4 == rt::Point(15, 0, 7));
		}

		TEST_METHOD(Transformation_Chained_Transformations_Applied_In_Reverse_Order)
		{
			rt::Point p(1, 0, 1);
			auto a = rt::rotation_x((f32)M_PI / 2);
			auto b = rt::scaling(5, 5, 5);
			auto c = rt::translation(10, 5, 7);

			auto t = c * b * a;
			Assert::IsTrue(t * p == rt::Point(15, 0, 7));
		}
	};
}