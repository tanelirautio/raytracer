#ifndef __APP_WINDOW_SDL_HPP__
#define __APP_WINDOW_SDL_HPP__

#include "rtDefs.hpp"
#include "appWindow.hpp"

#include <SDL.h>
#include <string>
#include <vector>
#include <mutex>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

namespace app {

	class WindowSDL : public Window {
	public:
		WindowSDL(i32 width, i32 height);
		WindowSDL(i32 width, i32 height, const std::vector<u8>& byte_array);
		~WindowSDL();

		void run();

		void pixel_changed(i32 x, i32 y, f32 r, f32 g, f32 b);
	private:
		void init(i32 width, i32 height, const std::vector<u8>& byte_array);
		void handle_events();


		SDL_Window* m_window = nullptr;
		SDL_Surface* m_window_surface = nullptr;
		SDL_Surface* m_surface = nullptr;
		SDL_Renderer* m_renderer = nullptr;

		int m_width;
		int m_height;
		bool m_running;
		std::vector<u8> m_byte_array;

		std::mutex m_surface_mutex;
	};

}

#endif


