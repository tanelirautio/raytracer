#include "rtTuple.hpp"
#include "rtFile.hpp"
#include "rtCanvas.hpp"
#include "rtLog.hpp"
#include "rtMatrix.hpp"
#include "rtDefs.hpp"


int main() {

	rt::Matrix I = rt::get_identity_matrix(4);
	auto invI = I.inverse();
	if (invI) {
		invI.value().debug_print();
	}
	else {
		LOG("Cannot invert!");
	}

	std::vector<f32> values_A = { 1, 2, 3, 4,
								 5, 6, 7, 8,
								9, 10, 11, 12,
								13,14,15,16 };

	rt::Matrix A(4, 4, { 1, 2, 3 });
	A.debug_print();
	return 0;
}