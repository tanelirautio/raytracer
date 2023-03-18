#include "appWindow.hpp"
#include <stdexcept>

namespace app {
	Window::Window(i32 width, i32 height) {
		init(width, height, {});
	}

	Window::Window(i32 width, i32 height, const std::vector<u8>& byte_array) {
		this->m_byte_array = byte_array;
		init(width, height, byte_array);
	}

	Window::~Window() {
		SDL_FreeSurface(m_window_surface);
		SDL_DestroyWindow(m_window);
		SDL_Quit();
	}

	void Window::init(i32 width, i32 height, const std::vector<u8>& byte_array) {
		if (SDL_Init(SDL_INIT_VIDEO) < 0) {
			std::string error = "SDL could not be initialized: ";
			throw(std::runtime_error((error + SDL_GetError()).c_str()));
		}

		m_window = SDL_CreateWindow("Raytracer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
		if (!m_window) {
			throw(std::runtime_error("Cannot initialize SDL window"));
		}

		m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
		if (!m_renderer) {
			std::string error = "Renderer could not be created: ";
			throw(std::runtime_error((error + SDL_GetError()).c_str()));
		}

		m_window_surface = SDL_GetWindowSurface(m_window);
		if (!m_window_surface) {
			throw(std::runtime_error("Failed to get window surface"));
		}

		m_width = width;
		m_height = height;
		m_byte_array = byte_array;
		m_running = true;
	}

	void Window::run() {
		if (m_byte_array.size() > 0) {
			m_surface = SDL_CreateRGBSurfaceFrom(&m_byte_array[0],
				m_width,
				m_height,
				24,
				m_width * 3,
				0x000000ff,
				0x0000ff00,
				0x00ff0000,
				0);
		}
		else {
			m_surface = SDL_CreateRGBSurface(0, 
				m_width, 
				m_height, 
				32, 
				0x000000ff,
				0x0000ff00,
				0x00ff0000,
				0);
		}
		if (!m_surface) {
			throw(std::runtime_error("Failed to create RGB surface"));
		}

		SDL_FillRect(m_surface, NULL, SDL_MapRGB(m_surface->format, 255, 0, 0));

		// The window is open: enter program loop (see SDL_PollEvent)
		while (m_running) {
			handle_events();

			// Lock the mutex before accessing the surface
			//std::lock_guard<std::mutex> lock(m_surface_mutex);
			//SDL_UpdateWindowSurface(m_window);
			//SDL_BlitSurface(m_surface, NULL, m_window_surface, NULL);
			SDL_Delay(10);
		}
		
	}

	/*
	void Window::pixel_changed(i32 x, i32 y, f32 r, f32 g, f32 b) {
		std::lock_guard<std::mutex> lock(m_surface_mutex);
		// Convert the color values to SDL-compatible format
		Uint32 color = SDL_MapRGB(m_surface->format, r * 255, g * 255, b * 255);

		// Get a pointer to the pixel at the specified coordinates
		Uint32* pixel = (Uint32*)m_surface->pixels + y * m_surface->pitch / 4 + x;

		// Set the pixel color
		*pixel = color;

		// Update the window display
		SDL_UpdateWindowSurface(m_window);
		SDL_BlitSurface(m_surface, NULL, m_window_surface, NULL);

	}
	*/
	
	void Window::pixel_changed(i32 x, i32 y, f32 r, f32 g, f32 b) {
		std::lock_guard<std::mutex> lock(m_surface_mutex);

		// Convert the color values to SDL-compatible format
		Uint32 color = SDL_MapRGB(m_surface->format, r * 255, g * 255, b * 255);

		// Get a pointer to the pixel at the specified coordinates
		Uint32* pixel = (Uint32*)m_surface->pixels + y * m_surface->pitch / 4 + x;

		// Set the pixel color
		*pixel = color;

		// Send an update event to the main thread
		SDL_Event event;
		event.type = SDL_USEREVENT;
		event.user.code = 0;
		event.user.data1 = nullptr;
		event.user.data2 = nullptr;
		SDL_PushEvent(&event);
	}
	
	void Window::handle_events() {
		SDL_Event sdl_event;
		while (SDL_PollEvent(&sdl_event) > 0) {
			switch (sdl_event.type) {
				case SDL_QUIT: {
					m_running = false;
					break;
				}
				case SDL_USEREVENT: {
					// Update the window display
					SDL_UpdateWindowSurface(m_window);
					SDL_BlitSurface(m_surface, NULL, m_window_surface, NULL);
					break;
				}
			}
		}
	}


}

