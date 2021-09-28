#ifndef __RT_CANVAS_HPP__
#define __RT_CANVAS_HPP__

#include "rtDefs.hpp"
#include "rtTuple.hpp"

#include <string>
#include <vector>

//TODO: add png support with stb_image_write:
//http://chanhaeng.blogspot.com/2018/12/how-to-use-stbimagewrite.html

namespace rt {

	class Canvas {
		public:
			Canvas(i32 width, i32 height);
			i32 width() const { return m_width;  }
			i32 height() const { return m_height; }

			void write_pixel(i32 x, i32 y, const Color& c);
			Color pixel_at(i32 x, i32 y) const;
			std::string canvas_to_ppm() const;
		private:
			i32 m_width;
			i32 m_height;
			std::vector<Color> m_data;
	};
}

#endif