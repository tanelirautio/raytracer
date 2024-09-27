#ifndef __APP_WINDOW_SDL_HPP__
#define __APP_WINDOW_SDL_HPP__

#include "rtDefs.hpp"
#include "appWindow.hpp"

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <vector>
#include <mutex>

namespace app {

	class WindowSDL : public Window {
	public:
		WindowSDL(i32 width, i32 height);
		~WindowSDL();

		void run();

		void pixel_changed(i32 x, i32 y, f32 r, f32 g, f32 b);
		void set_render_time(const std::string& render_time);
	private:
		void init();
		void handle_events();

		SDL_Window* m_window = nullptr;
		SDL_Renderer* m_renderer = nullptr;
		SDL_Surface* m_surface = nullptr;
		SDL_Texture* m_texture = nullptr;

		int m_width;
		int m_height;

		std::mutex m_surface_mutex;

		bool m_show_time = true; 
		std::string m_render_time_str; 
		TTF_Font* m_font;
		SDL_Surface* m_time_surface = nullptr;
		SDL_Rect m_time_rect;
		std::string m_last_render_time;
	};

}

#endif


