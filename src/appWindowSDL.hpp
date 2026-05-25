#ifndef __APP_WINDOW_SDL_HPP__
#define __APP_WINDOW_SDL_HPP__

#include "rtDefs.hpp"
#include "appWindow.hpp"

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <memory>
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
		void update_render_time_texture();

		struct SdlContext {
			~SdlContext();
		};

		using WindowPtr = std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)>;
		using RendererPtr = std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)>;
		using TexturePtr = std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)>;
		using FontPtr = std::unique_ptr<TTF_Font, decltype(&TTF_CloseFont)>;

		SdlContext m_sdl_context;
		WindowPtr m_window{ nullptr, SDL_DestroyWindow };
		RendererPtr m_renderer{ nullptr, SDL_DestroyRenderer };
		TexturePtr m_texture{ nullptr, SDL_DestroyTexture };

		int m_width = 0;
		int m_height = 0;

		std::mutex m_surface_mutex;
		std::vector<u8> m_pixels;

		bool m_show_time = true; 
		std::string m_render_time_str; 
		FontPtr m_font{ nullptr, TTF_CloseFont };
		TexturePtr m_time_texture{ nullptr, SDL_DestroyTexture };
		int m_time_width = 0;
		int m_time_height = 0;
		std::string m_last_render_time;
	};

}

#endif
