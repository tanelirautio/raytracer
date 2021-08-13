#include "rtTuple.hpp"
#include "rtFile.hpp"
#include "rtCanvas.hpp"
#include "rtLog.hpp"
#include "rtMatrix.hpp"


int main() {

	std::vector<float> values_A = { 0, 9, 3, 0,
									9, 8, 0, 8,
									1, 8, 5, 3,
									0, 0, 5, 8 };

	std::vector<float> values_B = { 0, 9, 1, 0,
									9, 8, 8, 0,
									3, 0, 5, 5 };

	rt::Matrix A(4, 4, values_A);
	rt::Matrix B(4, 3, values_B);

	rt::Matrix C = A.transpose();
	rt::Matrix D = B.transpose();

	LOG("---");
	A.print();
	LOG("---");
	C.print();

	LOG("#####");
	LOG("#####");
	B.print();
	LOG("---");
	D.print();

	return 0;
}