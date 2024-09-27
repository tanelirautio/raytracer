#ifndef __APP_WINDOW_HPP__
#define __APP_WINDOW_HPP__

#include "rtDefs.hpp"
#include <string>

namespace app {

	class Window {
		public:
			enum class Type {
				SDL,
				CLI,
			};
			Window(Type type) {
				m_type = type;
			}
			virtual ~Window() {}
			virtual void run() = 0;
			virtual void pixel_changed(i32 x, i32 y, f32 r, f32 g, f32 b) = 0;
			virtual void set_render_time(const std::string& render_time) = 0;

			Type type() const { return m_type; }
		private:
			Type m_type;
	};

}

#endif


