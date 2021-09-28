#include "appSphere2.hpp"

#include "rtMain.hpp"
#include <chrono>
#include <iostream>
#include <vector>
#include <memory>
#include <string>


int main() {
	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

	app::Sphere2 app;
	app.create();
	
	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
	std::cout << "Execution time = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;
	return 0;
}