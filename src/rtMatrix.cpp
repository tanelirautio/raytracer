#include "rtMatrix.hpp"
#include "rtUtil.hpp"

namespace rt {

	Matrix::Matrix(i32 rows, i32 cols) {
		m_rows = rows;
		m_cols = cols;

		m_matrix.resize(rows);
		for (auto& col : m_matrix) {
			col.resize(cols);
		}
	}

	Matrix::Matrix(i32 rows, i32 cols, std::vector<f32> values) : Matrix(rows, cols) {
		//TODO: sanity check for values
		i32 i = 0;
		for (i32 r = 0; r < m_rows; r++) {
			for (i32 c = 0; c < m_cols; c++) {
				m_matrix[r][c] = values[i];
				i++;
			}
		}
	}

	f32 Matrix::at(i32 row, i32 col) const {
		//TODO: sanity check
		return m_matrix[row][col];
	}

	std::pair<f32, f32> Matrix::get_size() const {
		return std::pair<f32, f32>(std::make_pair(m_rows, m_cols));
	}

	bool operator==(const Matrix& lhs, const Matrix& rhs) {
		if (lhs.get_size() != rhs.get_size()) {
			return false;
		}
		
		const auto& size = lhs.get_size();
		for (i32 r = 0; r < size.first; r++) {
			for (i32 c = 0; c < size.second; c++) {
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

}
