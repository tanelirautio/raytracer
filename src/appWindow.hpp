#ifndef __APP_WINDOW_HPP__
#define __APP_WINDOW_HPP__

#include "appState.hpp"
#include "rtDefs.hpp"
#include "rtTuple.hpp"
#include <memory>
#include <string>
#include <vector>

namespace app {

	class Window {
		public:
			enum class Type {
				SDL,
				CLI,
			};
			Window(Type type) : m_type(type) {}
			virtual ~Window() {}
			virtual void run(AppState& state) = 0;
			virtual void row_changed(i32 y, const std::vector<rt::Color>& row) = 0;
			virtual void set_render_time(const std::string& render_time) = 0;

			Type type() const { return m_type; }
		private:
			Type m_type = Type::CLI;
	};

	std::unique_ptr<Window> create_window(i32 width, i32 height);

}

#endif
