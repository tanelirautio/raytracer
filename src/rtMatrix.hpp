#ifndef __RT_MATRIX_HPP__
#define __RT_MATRIX_HPP__

#include <vector>

#include "rtDefs.hpp"

namespace rt {
	class Matrix {
		public:
			Matrix(i32 w, i32 h);
			Matrix(i32 w, i32 h, std::vector<f32> values);
			f32 at(i32 row, i32 col);
		private:
			std::vector<std::vector<f32>> m_matrix;
			i32 m_rows;
			i32 m_cols;
	};
}

#endif