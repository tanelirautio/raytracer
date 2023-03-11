#ifndef __APP_SPHERE_2_HPP__
#define __APP_SPHERE_2_HPP__

#include "rtCanvas.hpp"

namespace app {
	class Sphere2 {
	public:
		Sphere2() : width(0), height(0) {};
		~Sphere2() = default;
		rt::Canvas create(const std::string& image_name, int width = 150, int height = 100);
	private:
		int width;
		int height;
	};
}

#endif