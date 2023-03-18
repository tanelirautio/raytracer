//include "appSphere.hpp"
//include "appSphere2.hpp"
#include "appSphere3.hpp"

#include "rtMain.hpp"
#include "appWindow.hpp"

#include <chrono>
#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <thread>

const i32 WIDTH = 320;
const i32 HEIGHT = 200;

void render_thread_function(app::Window& w) {
	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
	
	app::Sphere3 s(WIDTH, HEIGHT);
	s.set_window_callback(w);
	rt::Canvas canvas = s.create();

	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

	auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
	auto time_str = rt::format_duration(ms);
	std::cout << "Time to render the image: " << time_str << std::endl;

	//TODO: optional image writing
	std::string name = "spheres_with_different_patterns.ppm";
	rt::write_file(name, canvas.canvas_to_ppm());
}


int main(int argc, char** argv) {

	try {
		app::Window w(WIDTH, HEIGHT);
		std::thread render_thread(render_thread_function, std::ref(w));
		w.run();
		render_thread.join();
	}
	catch (const std::exception& e) {
		std::cout << "Error creating SDL window";
		std::cout << e.what();
	}

	return 0;
}