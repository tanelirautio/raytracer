#ifndef __APP_SPHERE_3_HPP__
#define __APP_SPHERE_3_HPP__

#include "rtCanvas.hpp"

namespace app {
	class Sphere3 {
	public:
		Sphere3() : width(0), height(0) {};
		~Sphere3() = default;
		rt::Canvas create(const std::string& image_name, int width = 150, int height = 100);
	private:
		int width;
		int height;
	};
}

#endif