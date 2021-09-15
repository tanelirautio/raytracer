#include "appSphere.hpp"

#include "rtMain.hpp"
#include <chrono>
#include <iostream>

int main() {
	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

	rt::World w = rt::get_default_world();
	rt::Ray r({ 0,0,-5 }, { 0,0,1 });

	auto xs = w.intersect(r);

	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
	std::cout << "Execution time = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;
	return 0;
}