#ifndef __RT_MATRIX_HPP__
#define __RT_MATRIX_HPP__

#include <vector>

#include "rtDefs.hpp"
#include <utility>
#include "rtTuple.hpp"

namespace rt {
	class Matrix {
		public:
			struct MatrixSize {
				MatrixSize() {};
				MatrixSize(const std::pair<i32, i32>& size) { m_size = size; }
				i32 rows() const { return m_size.first; }
				i32 cols() const { return m_size.second; }
				std::pair<i32, i32> m_size;
			};

			Matrix(i32 w, i32 h);
			Matrix(i32 w, i32 h, std::vector<f32> values);
			f32 at(i32 row, i32 col) const;
			MatrixSize get_size() const;

			Matrix transpose();

			static Matrix get_identity();
		private:
			std::vector<std::vector<f32>> m_matrix;
			MatrixSize m_size;
	};

	bool operator==(const Matrix& lhs, const Matrix& rhs);
	bool operator!=(const Matrix& lhs, const Matrix& rhs);
	Matrix operator*(const Matrix& lhs, const Matrix& rhs);
	Tuple operator*(const Matrix& lhs, const Tuple& rhs);
}

#endif