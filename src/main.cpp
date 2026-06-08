#include "appScene.hpp"
#include "appState.hpp"
#include "rtMain.hpp"
#include "appWindow.hpp"
#include <SDL3/SDL_main.h>


#include <chrono>
#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <thread>

const i32 WIDTH = 640;
const i32 HEIGHT = 400;

void render_thread_function(app::Window* w, app::AppState& state, const std::string& scene_name) {
	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
	
	auto scene = app::make_scene(scene_name, WIDTH, HEIGHT);
	scene.camera.set_row_callback([w](i32 y, const std::vector<rt::Color>& row) {
		w->row_changed(y, row);
	});

	rt::Canvas canvas = scene.camera.render(scene.world, [&state] {
		return !state.running.load();
	});
	
	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

	auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
	auto time_str = rt::format_minute_seconds(ms);
	LOG("Time to render scene '%s': %s", scene.name.c_str(), time_str.c_str());

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
	app::AppState state;
	std::string scene_name = argc > 1 ? argv[1] : std::string(app::default_scene_name());

	auto window = app::create_window(WIDTH, HEIGHT);
    
    std::thread render_thread([&] {
        render_thread_function(window.get(), state, scene_name);
    });
    window->run(state);
    render_thread.join();

    return 0;
}
