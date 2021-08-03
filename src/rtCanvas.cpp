#include "rtCanvas.hpp"

#include <cassert>

namespace rt {

	Canvas::Canvas(i32 width, i32 height) {
		m_width = width;
		m_height = height;

		m_data.reserve(width * height);
		m_data.resize(width*height);
	}

	void Canvas::write_pixel(i32 x, i32 y, const rt::Color& c)  {
		m_data[x + y * m_width] = c;
	}

	rt::Color Canvas::pixel_at(i32 x, i32 y) const {
		return m_data[x + y * m_width];
	}

}