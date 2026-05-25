#ifndef __APP_STATE_HPP__
#define __APP_STATE_HPP__

#include <atomic>

namespace app {
	struct AppState {
		std::atomic<bool> running = true;
	};
}

#endif
