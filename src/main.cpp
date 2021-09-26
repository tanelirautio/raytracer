#include "appSphere.hpp"

#include "rtMain.hpp"
#include <chrono>
#include <iostream>
#include <vector>
#include <memory>
#include <string>

int main() {
	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();


	rt::Camera c(201, 101, HALF_PI);
	c.transform() = rt::rotation_y(M_PI / 4.f) * rt::translation(0, -2, 5);
	rt::Ray r = c.ray_for_pixel(100, 50);
	r.debug_print();

	LOG("---");

	rt::Ray expected_result(rt::Point(0, 2, -5), rt::Vector(sqrt(2.f) / 2.f, 0, -sqrt(2.f) / 2.f));
	expected_result.debug_print();

	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
	std::cout << "Execution time = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;
	return 0;
}