#include "appState.hpp"
#include "appWindowSDL.hpp"
#include <stdexcept>

namespace app {
	WindowSDL::WindowSDL(i32 width, i32 height) : Window(Type::SDL) {
		m_width = std::max(width, 320);
		m_height = std::max(height, 200);
		init();
	}

	WindowSDL::~WindowSDL() {
		if (m_renderer) {
			SDL_DestroyRenderer(m_renderer);
		}
		if (m_window) {
			SDL_DestroyWindow(m_window);
		}
		if (m_time_surface) {
			SDL_FreeSurface(m_time_surface);
		}
		if (m_font) {
			TTF_CloseFont(m_font);
		}
		TTF_Quit();
		SDL_Quit();
	}

	void WindowSDL::init() {
		if (SDL_Init(SDL_INIT_VIDEO) < 0) {
			std::string error = "SDL could not be initialized: ";
			throw(std::runtime_error((error + SDL_GetError()).c_str()));
		}

		m_window = SDL_CreateWindow("Raytracer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_width, m_height, 0);
		if (!m_window) {
			throw(std::runtime_error("Cannot initialize SDL window"));
		}

		m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
		if (!m_renderer) {
			std::string error = "Renderer could not be created: ";
			throw(std::runtime_error((error + SDL_GetError()).c_str()));
		}

		if (TTF_Init() == -1) {
			throw(std::runtime_error("SDL_ttf could not be initialized"));
		}

		m_font = TTF_OpenFont("assets/OpenSans-Regular.ttf", 16);
		if (!m_font) {
			throw(std::runtime_error("Failed to load font"));
		}

		m_surface = SDL_CreateRGBSurface(0, m_width, m_height, 32,
			0x00FF0000,  // Red mask (bits 16–23)
			0x0000FF00,  // Green mask (bits 8–15)
			0x000000FF,  // Blue mask (bits 0–7)
			0xFF000000); // Alpha mask (bits 24–31)
		if (!m_surface) {
			throw(std::runtime_error("Failed to create surface"));
		}
		SDL_SetSurfaceBlendMode(m_surface, SDL_BLENDMODE_BLEND);

		Uint32 blue_color = SDL_MapRGB(m_surface->format, 0, 0, 255);
		SDL_FillRect(m_surface, NULL, blue_color);  

		m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, m_width, m_height);
		if (!m_texture) {
			throw(std::runtime_error("Failed to create texture"));
		}
	}

	void WindowSDL::run() {
		while (g_app_running) {
			handle_events();

			std::lock_guard<std::mutex> lock(m_surface_mutex);

			SDL_UpdateTexture(m_texture, NULL, m_surface->pixels, m_surface->pitch);
			SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);  
			SDL_RenderClear(m_renderer);
			SDL_RenderCopy(m_renderer, m_texture, NULL, NULL);

			if (m_time_surface) {
				SDL_Rect dst_rect = { 10, m_height - 30, m_time_surface->w, m_time_surface->h }; 
				SDL_BlitSurface(m_time_surface, NULL, m_surface, &dst_rect); 
			}

			SDL_RenderPresent(m_renderer);

			SDL_Delay(0);
		}
	}

	void WindowSDL::pixel_changed(i32 x, i32 y, f32 r, f32 g, f32 b) {
		std::lock_guard<std::mutex> lock(m_surface_mutex);

		Uint8 red = static_cast<Uint8>(r * 255);
		Uint8 green = static_cast<Uint8>(g * 255);
		Uint8 blue = static_cast<Uint8>(b * 255);

		Uint32 pixel_color = SDL_MapRGB(m_surface->format, red, green, blue);

		Uint32* pixels = (Uint32*)m_surface->pixels;
		pixels[(y * m_width) + x] = pixel_color;
	}

	void WindowSDL::handle_events() {
		SDL_Event sdl_event;
		while (SDL_PollEvent(&sdl_event) > 0) {
			switch (sdl_event.type) {
				case SDL_QUIT: {
					g_app_running = false;
					break;
				}
				case SDL_KEYDOWN: {
					if (sdl_event.key.keysym.sym == SDLK_ESCAPE) {
						g_app_running = false;
					}
					else if (sdl_event.key.keysym.sym == SDLK_t) {
						m_show_time = !m_show_time; 
					}
					break;
				}
			}
		}
	}

	void WindowSDL::set_render_time(const std::string& render_time) {
		if (render_time != m_last_render_time) {
			if (m_time_surface) {
				SDL_FreeSurface(m_time_surface);
				m_time_surface = nullptr; 
			}

			SDL_Color color = { 255, 255, 255 }; // White color
			m_time_surface = TTF_RenderText_Blended(m_font, render_time.c_str(), color);
			if (!m_time_surface) {
				throw(std::runtime_error("Failed to create text surface"));
			}

			m_last_render_time = render_time;
		}
	}
}

