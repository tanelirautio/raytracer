#include "appState.hpp"
#include "appWindowSDL.hpp"
#include <algorithm>
#include <cmath>
#include <stdexcept>

namespace app {
	WindowSDL::SdlContext::~SdlContext() {
		TTF_Quit();
		SDL_Quit();
	}

	WindowSDL::WindowSDL(i32 width, i32 height) : Window(Type::SDL) {
		m_width = std::max(width, 320);
		m_height = std::max(height, 200);
		init();
	}

	WindowSDL::~WindowSDL() {
		// SDL resources are owned by unique_ptr members and destroyed before m_sdl_context.
	}

	void WindowSDL::init() {
		if (!SDL_Init(SDL_INIT_VIDEO)) {
			std::string error = "SDL could not be initialized: ";
			throw(std::runtime_error((error + SDL_GetError()).c_str()));
		}

		m_window.reset(SDL_CreateWindow("Raytracer", m_width, m_height, 0));
		if (!m_window) {
			throw(std::runtime_error("Cannot initialize SDL window"));
		}

		m_renderer.reset(SDL_CreateRenderer(m_window.get(), nullptr));
		if (!m_renderer) {
			std::string error = "Renderer could not be created: ";
			throw(std::runtime_error((error + SDL_GetError()).c_str()));
		}

		if (!TTF_Init()) {
			throw(std::runtime_error("SDL_ttf could not be initialized"));
		}

		m_font.reset(TTF_OpenFont("assets/OpenSans-Regular.ttf", 16.0f));
		if (!m_font) {
			throw(std::runtime_error("Failed to load font"));
		}

		m_pixels.resize(static_cast<size_t>(m_width) * static_cast<size_t>(m_height) * 3, 0);
		for (size_t i = 0; i < m_pixels.size(); i += 3) {
			m_pixels[i + 2] = 255;
		}

		m_texture.reset(SDL_CreateTexture(m_renderer.get(), SDL_PIXELFORMAT_RGB24, SDL_TEXTUREACCESS_STREAMING, m_width, m_height));
		if (!m_texture) {
			throw(std::runtime_error("Failed to create texture"));
		}
	}

	void WindowSDL::run() {
		while (g_app_running) {
			handle_events();

			std::lock_guard<std::mutex> lock(m_surface_mutex);

			update_render_time_texture();

			SDL_UpdateTexture(m_texture.get(), nullptr, m_pixels.data(), m_width * 3);
			SDL_SetRenderDrawColor(m_renderer.get(), 0, 0, 0, 255);
			SDL_RenderClear(m_renderer.get());
			SDL_RenderTexture(m_renderer.get(), m_texture.get(), nullptr, nullptr);

			if (m_show_time && m_time_texture) {
				SDL_FRect dst_rect = { 10.0f, static_cast<float>(m_height - 30), static_cast<float>(m_time_width), static_cast<float>(m_time_height) };
				SDL_RenderTexture(m_renderer.get(), m_time_texture.get(), nullptr, &dst_rect);
			}

			SDL_RenderPresent(m_renderer.get());

			SDL_Delay(0);
		}
	}

	void WindowSDL::pixel_changed(i32 x, i32 y, f32 r, f32 g, f32 b) {
		if (x < 0 || x >= m_width || y < 0 || y >= m_height) {
			return;
		}

		std::lock_guard<std::mutex> lock(m_surface_mutex);

		Uint8 red = static_cast<Uint8>(std::clamp(static_cast<i32>(std::round(r * 255.f)), 0, 255));
		Uint8 green = static_cast<Uint8>(std::clamp(static_cast<i32>(std::round(g * 255.f)), 0, 255));
		Uint8 blue = static_cast<Uint8>(std::clamp(static_cast<i32>(std::round(b * 255.f)), 0, 255));

		size_t offset = (static_cast<size_t>(y) * static_cast<size_t>(m_width) + static_cast<size_t>(x)) * 3;
		m_pixels[offset] = red;
		m_pixels[offset + 1] = green;
		m_pixels[offset + 2] = blue;
	}

	void WindowSDL::handle_events() {
		SDL_Event sdl_event;
		while (SDL_PollEvent(&sdl_event)) {
			switch (sdl_event.type) {
				case SDL_EVENT_QUIT: {
					g_app_running = false;
					break;
				}
				case SDL_EVENT_KEY_DOWN: {
					if (sdl_event.key.scancode == SDL_SCANCODE_ESCAPE) {
						g_app_running = false;
					}
					else if (sdl_event.key.scancode == SDL_SCANCODE_T) {
						m_show_time = !m_show_time;
					}
					break;
				}
			}
		}
	}

	void WindowSDL::set_render_time(const std::string& render_time) {
		std::lock_guard<std::mutex> lock(m_surface_mutex);
		m_render_time_str = render_time;
	}

	void WindowSDL::update_render_time_texture() {
		if (m_render_time_str.empty() || m_render_time_str == m_last_render_time) {
			return;
		}

		if (m_time_texture) {
			m_time_texture.reset();
		}

		SDL_Color color = { 255, 255, 255, 255 };
		SDL_Surface* time_surface = TTF_RenderText_Blended(m_font.get(), m_render_time_str.c_str(), m_render_time_str.size(), color);
		if (!time_surface) {
			throw(std::runtime_error("Failed to create text surface"));
		}

		m_time_texture.reset(SDL_CreateTextureFromSurface(m_renderer.get(), time_surface));
		if (!m_time_texture) {
			SDL_DestroySurface(time_surface);
			throw(std::runtime_error("Failed to create text texture"));
		}

		m_time_width = time_surface->w;
		m_time_height = time_surface->h;
		SDL_DestroySurface(time_surface);

		m_last_render_time = m_render_time_str;
	}
}
