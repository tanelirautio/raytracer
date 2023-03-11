#include "rtDefs.hpp"

#include <SDL.h>
#include <string>
#include <vector>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

namespace app {

	class Window {
		public:
			Window(int width, int height, const std::vector<u8>& byte_array);
			~Window();

			void run();


		private:
			void handle_events();
	

			SDL_Window* m_window = nullptr;
			SDL_Surface* m_window_surface = nullptr;
			SDL_Renderer* m_renderer = nullptr;

			int width;
			int height;
			bool m_running;
			std::vector<u8> byte_array;
	};

}


