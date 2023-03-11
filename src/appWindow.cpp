#include "appWindow.hpp"
#include <stdexcept>

namespace app {
	Window::Window(int width, int height, const std::vector<u8>& byte_array) : m_running(true) {

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

		this->width = width;
		this->height = height;
		this->byte_array = byte_array;

		run(); 
	}

	Window::~Window() {
		SDL_FreeSurface(m_window_surface);
		SDL_DestroyWindow(m_window);
		SDL_Quit();
	}

	void Window::run() {
		SDL_Surface* surface = SDL_CreateRGBSurfaceFrom(&byte_array[0],
			width,
			height,
			24,
			width * 3,
			0x000000ff,
			0x0000ff00,
			0x00ff0000,
			0);

		SDL_BlitSurface(surface, NULL, m_window_surface, NULL);
		SDL_UpdateWindowSurface(m_window);

		// The window is open: enter program loop (see SDL_PollEvent)
		while (m_running) {
			handle_events();
		}
		
	}

	void Window::handle_events() {
		SDL_Event sdl_event;
		while (SDL_PollEvent(&sdl_event) > 0) {
			switch (sdl_event.type) {
				case SDL_QUIT: {
					m_running = false;
					break;
				}				
			}
		}
	}


}

