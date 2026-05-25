#include "appWindow.hpp"
#include "appWindowSDL.hpp"

namespace app {

	std::unique_ptr<Window> create_window(i32 width, i32 height) {
		return std::make_unique<WindowSDL>(width, height);
	}

}
