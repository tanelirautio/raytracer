#include "rtMatrix.hpp"
#include "rtUtil.hpp"

namespace rt {

	Matrix::Matrix(i32 rows, i32 cols) {
		m_size = MatrixSize(std::pair<i32,i32>(std::make_pair(rows, cols)));

		m_matrix.resize(rows);
		for (auto& col : m_matrix) {
			col.resize(cols);
		}
	}

	Matrix::Matrix(i32 rows, i32 cols, std::vector<f32> values) : Matrix(rows, cols) {
		//TODO: sanity check for values
		i32 i = 0;
		for (i32 r = 0; r < m_size.rows(); r++) {
			for (i32 c = 0; c < m_size.cols(); c++) {
				m_matrix[r][c] = values[i];
				i++;
			}
		}
	}

	f32 Matrix::at(i32 row, i32 col) const {
		//TODO: sanity check
		return m_matrix[row][col];
	}

	Matrix::MatrixSize Matrix::get_size() const {
		return m_size;
	}

	Matrix Matrix::get_identity() {
		std::vector<f32> v{ 1, 0, 0, 0,
							0, 1, 0, 0,
							0, 0, 1, 0,
							0, 0, 0, 1 };
		return Matrix(4, 4, v);
	}

	bool operator==(const Matrix& lhs, const Matrix& rhs) {
		if (lhs.get_size().m_size != rhs.get_size().m_size) {
			return false;
		}
		
		const auto& size = lhs.get_size();
		for (i32 r = 0; r < size.rows(); r++) {
			for (i32 c = 0; c < size.cols(); c++) {
				if (!equal(lhs.at(r, c), rhs.at(r, c))) {
					return false;
				}
			}
		}

		return true;
	}

	bool operator!=(const Matrix& lhs, const Matrix& rhs) {
		return !(lhs == rhs);
	}

	// Note: works only for 4x4 matrices
	Matrix operator*(const Matrix& lhs, const Matrix& rhs) {
		std::vector<f32> values;
		f32 v = 0;

		for (i32 r = 0; r < lhs.get_size().rows(); r++) {
			for (i32 c = 0; c < lhs.get_size().cols(); c++) {
				v = lhs.at(r, 0) * rhs.at(0, c) +
					lhs.at(r, 1) * rhs.at(1, c) +
					lhs.at(r, 2) * rhs.at(2, c) +
					lhs.at(r, 3) * rhs.at(3, c);
				values.emplace_back(v);
			}
		}

		return Matrix(4, 4, values);
	}

	Tuple operator*(const Matrix& lhs, const Tuple& rhs)
	{
		std::vector<f32> values;
		f32 v = 0;

		for (i32 r = 0; r < lhs.get_size().rows(); r++) {
				v = lhs.at(r, 0) * rhs.x() +
					lhs.at(r, 1) * rhs.y() +
					lhs.at(r, 2) * rhs.z() +
					lhs.at(r, 3) * rhs.w();
				values.emplace_back(v);
			
		}

		return Tuple(values[0], values[1], values[2], values[3]);
	}



}
