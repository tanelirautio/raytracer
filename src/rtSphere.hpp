#ifndef __RT_SPHERE_HPP__
#define __RT_SPHERE_HPP__

#include "rtDefs.hpp"

namespace rt {
	class Sphere {
		public:
			Sphere();
			i32 id() const { return ID; }
		private:
			static i32 ID;
	};
}

#endif