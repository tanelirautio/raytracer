#include "appSphere.hpp"

#include "rtMain.hpp"
#include <chrono>
#include <iostream>
#include <vector>
#include <memory>
#include <string>

int main() {
	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

	// DO STUFF
	rt::World w = rt::get_default_world();
	rt::Ray r({ 0,0,-5 }, { 0,0,1 });
	auto shape = w.get_objects().at(0);
	rt::Intersection i(4, shape.get());
	rt::Computations comps = rt::prepare_computations(i, r);
	rt::Color c = w.shade_hit(comps);
	c.debug_print();

	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
	std::cout << "Execution time = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;
	return 0;
}