#include "rtMatrix.hpp"
#include "rtMatrix.hpp"
#include "rtUtil.hpp"
#include "rtLog.hpp"

namespace rt {

	Matrix::Matrix(i32 rows, i32 cols) {
		m_size = Size(std::pair<i32,i32>(std::make_pair(rows, cols)));

		m_matrix.resize(rows);
		for (auto& col : m_matrix) {
			col.resize(cols);
		}
	}

	Matrix::Matrix(i32 rows, i32 cols, std::vector<f32> values) : Matrix(rows, cols) {
		i32 i = 0;
		for (i32 r = 0; r < m_size.rows(); r++) {
			for (i32 c = 0; c < m_size.cols(); c++) {
				if (i < values.size()) {
					m_matrix[r][c] = values[i];
				}
				else {
					m_matrix[r][c] = 0;
				}
				i++;
			}
		}
	}

	f32 Matrix::at(i32 row, i32 col) const {
		return m_matrix[row][col];
	}

	void Matrix::set(i32 row, i32 col, f32 value) {
		m_matrix[row][col] = value;
	}

	Matrix::Size Matrix::get_size() const {
		return m_size;
	}

	Matrix Matrix::transpose() {
		Matrix transposed = Matrix(get_size().cols(), get_size().rows());
				
		for (i32 r = 0; r < get_size().rows(); r++) {
			for (i32 c = 0; c < get_size().cols(); c++) {
				transposed.set(c, r, at(r,c));
			}
		}

		return transposed;
	}

	f32 Matrix::determinant() const {
		f32 det = 0;
		if (m_size.rows() == 2 && m_size.cols() == 2) {
			det = at(0, 0) * at(1, 1) - at(0, 1) * at(1, 0);
		}
		else {
			for (i32 c = 0; c < m_size.cols(); c++) {
				det = det + at(0, c) * cofactor(0, c);
			}
		}
		return det;
	}

	Matrix Matrix::submatrix(i32 row, i32 col) const {		
		std::vector<f32> values;
		for (i32 r = 0; r < m_size.rows(); r++) {
			for (i32 c = 0; c < m_size.cols(); c++) {
				if (r != row && c != col) {
					values.emplace_back(at(r, c));
				}
			}
		}
		return Matrix(m_size.rows() - 1, m_size.cols() - 1, values);
	}

	f32 Matrix::minor(i32 row, i32 col) const {
		Matrix m = submatrix(row, col);
		return m.determinant();
	}

	f32 Matrix::cofactor(i32 row, i32 col) const {
		f32 cofactor = minor(row, col);
		return (row + col) % 2 == 0 ? cofactor : -cofactor;
	}

	std::optional<Matrix> Matrix::inverse() const {
		if (determinant() == 0) {
			return std::nullopt;
		}

		Matrix m(m_size.rows(), m_size.cols());
		for (i32 row = 0; row < m_size.rows(); row++) {
			for (i32 col = 0; col < m_size.cols(); col++) {
				f32 c = cofactor(row, col);
				m.set(col, row, (c / determinant()));
			}
		}

		return m;
	}

	void Matrix::debug_print() {
		std::string row;

		for (i32 r = 0; r < m_size.rows(); r++) {
			for (i32 c = 0; c < m_size.cols(); c++) {
				f32 value = m_matrix[r][c];
				row += std::to_string(value) + " ";
			}
			LOG("%s", row.c_str());
			row.clear();
		}

	}

	Matrix get_identity_matrix(i32 dimension) {
		Matrix identity = Matrix(dimension, dimension);
		for (i32 i = 0; i < dimension; i++) {
			identity.set(i, i, 1);
		}
		return identity;
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
