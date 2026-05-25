#ifndef __APP_SPHERE_2_HPP__
#define __APP_SPHERE_2_HPP__

#include "rtCanvas.hpp"

namespace app {
	class Sphere2 {
	public:
		Sphere2() = default;
		~Sphere2() = default;
		rt::Canvas create(const std::string& image_name, int width = 150, int height = 100);
	private:
		int width = 0;
		int height = 0;
	};
}

#endif
