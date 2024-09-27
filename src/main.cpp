//include "appSphere.hpp"
//include "appSphere2.hpp"
#include "appSphere3.hpp"

#include "appState.hpp"
#include "rtMain.hpp"
#include "appWindow.hpp"
#include "appWindowSDL.hpp"


#include <chrono>
#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <thread>

const i32 WIDTH = 160;
const i32 HEIGHT = 100;

void render_thread_function(app::Window* w) {
	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
	
	app::Sphere3 s(WIDTH, HEIGHT);
	s.set_window_callback(*w);
	rt::Canvas canvas = s.create();
	
	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

	auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
	auto time_str = rt::format_minute_seconds(ms);
	LOG("Time to render the image: %s", time_str.c_str());

	w->set_render_time(time_str);

	/*
	// OPTIONAL: image saving
	begin = std::chrono::steady_clock::now();

	std::string name = "spheres_with_different_patterns.ppm";
	rt::write_file(name, canvas.canvas_to_ppm());

	end = std::chrono::steady_clock::now();

	ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
	time_str = rt::format_duration(ms);
	LOG("Time to write the image: %s", time_str.c_str());
	*/
}


int main(int argc, char** argv) {
	g_app_running = true;

    app::Window* window = nullptr;
    window = new app::WindowSDL(WIDTH, HEIGHT);
    
    std::thread render_thread(render_thread_function, window);
    window->run(); 
    render_thread.join();

    if (window) {
        delete window; 
    }
    return 0;
}
