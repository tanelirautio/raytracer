#ifndef __APP_SPHERE_3_HPP__
#define __APP_SPHERE_3_HPP__

#include "rtCanvas.hpp"
#include <memory>
#include "appWindow.hpp"
#include "rtCamera.hpp"

namespace app {
	class Sphere3 {
	public:
		Sphere3(i32 width, i32 height); 
		~Sphere3() = default;
		rt::Canvas create();
		void set_window_callback(app::Window& w);
	private:
		i32 m_width;
		i32 m_height;
		std::unique_ptr<rt::Camera> m_camera;
	};
}

#endif