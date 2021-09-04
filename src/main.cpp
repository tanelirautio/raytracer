//#include "appClock.hpp"
#include "appSphere.hpp"

#include "rtLog.hpp"
#include "rtDefs.hpp"
#include <chrono>


#include <iostream>

int main() {
	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

	//app::Clock clock;
	//clock.create();

	app::Sphere sphere;
	sphere.create();

	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
	std::cout << "Execution time = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;
	return 0;
}