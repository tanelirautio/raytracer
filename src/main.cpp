#include "rtTuple.hpp"
#include "rtFile.hpp"
#include "rtCanvas.hpp"
#include "rtLog.hpp"
#include "rtMatrix.hpp"
#include "rtDefs.hpp"


int main() {

	std::vector<float> values_A = { 1, 2, 6,
									-5, 8, -4,
									2, 6, 4 };
	rt::Matrix A(3, 3, values_A);

	f32 det = A.determinant();
	LOG("%f", det);
	
	return 0;
}