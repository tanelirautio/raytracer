//include "appSphere.hpp"
//include "appSphere2.hpp"
#include "appSphere3.hpp"

#include "rtMain.hpp"
#include <chrono>
#include <iostream>
#include <vector>
#include <memory>
#include <string>

#define USE_SDL

#ifdef USE_SDL
#include "appWindow.hpp"
#endif


int main(int argc, char** argv) {
	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

	app::Sphere3 s;
	rt::Canvas canvas = s.create("spheres_with_different_patterns", 150, 100);

	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

#ifdef USE_SDL
	try {
		app::Window w(canvas.width(), canvas.height(), canvas.to_bytearray());
	}
	catch (const std::exception& e) {
		std::cout << "Error creating SDL window";
		std::cout << e.what();
	}
#endif


	auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
	auto time_str = rt::format_duration(ms);
	std::cout << "Time to render the image: " << time_str << std::endl;
	return 0;
}