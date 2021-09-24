#ifndef __RT_MATRIX_HPP__
#define __RT_MATRIX_HPP__

#include <vector>

#include "rtDefs.hpp"
#include "rtTuple.hpp"

#include <utility>
#include <optional>

namespace rt {
	class Matrix {
		public:
			struct Size {
				Size() {};
				Size(const std::pair<i32, i32>& size) { m_size = size; }
				i32 rows() const { return m_size.first; }
				i32 cols() const { return m_size.second; }
				std::pair<i32, i32> m_size;
			};

			Matrix() : Matrix(4, 4) {}
			Matrix(i32 w, i32 h);
			Matrix(i32 w, i32 h, const std::vector<f32>& values);
			f32 at(i32 row, i32 col) const;
			void set(i32 row, i32 col, f32 value);
			Size size() const;

			Matrix transpose();
			f32 determinant() const;
			Matrix submatrix(i32 row, i32 col) const;
			f32 minor(i32 row, i32 col) const;
			f32 cofactor(i32 row, i32 col) const;
			std::optional<Matrix> inverse() const;

			void debug_print();

		protected:
			std::vector<std::vector<f32>> m_matrix;
			Size m_size;
	};

	class Matrix4 : public Matrix {
		public:
			Matrix4(const std::vector<f32>& values) : Matrix(4, 4, values) {}
	};

	class Matrix3 : public Matrix {
		public:
			Matrix3(const std::vector<f32>& values) : Matrix(3, 3, values) {}
	};

	class Matrix2 : public Matrix {
		public:
			Matrix2(const std::vector<f32>& values) : Matrix(2, 2, values) {}
	};

	Matrix get_identity_matrix(i32 dimension);
	std::optional<Matrix> inverse(const Matrix& m);

	bool operator==(const Matrix& lhs, const Matrix& rhs);
	bool operator!=(const Matrix& lhs, const Matrix& rhs);
	Matrix operator*(const Matrix& lhs, const Matrix& rhs);
	Tuple operator*(const Matrix& lhs, const Tuple& rhs);
}

#endif