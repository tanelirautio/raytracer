#include "rtCanvas.hpp"

#include <sstream>
#include <iterator>
#include <algorithm>

namespace rt {

	const i32 PPM_MAX_LINE_LENGTH = 70;

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

	std::string Canvas::canvas_to_ppm() const {
		std::string header = "P3\n" + std::to_string(m_width) + " " + std::to_string(m_height) + "\n255\n";
		
		std::vector<std::string> data;

		std::string current_line;
		for (i32 y = 0; y < m_height; y++) {
			for (i32 x = 0; x < m_width; x++) {
				auto c = pixel_at(x, y);
				auto r = static_cast<i32>(std::round(c.r() * 255.f));
				auto g = static_cast<i32>(std::round(c.g() * 255.f));
				auto b = static_cast<i32>(std::round(c.b() * 255.f));

				r = std::clamp(r, 0, 255);
				g = std::clamp(g, 0, 255);
				b = std::clamp(b, 0, 255);

				std::string entry = std::to_string(r) + " " + std::to_string(g) + " " + std::to_string(b);

				if (current_line.size() + entry.size() + 2 > PPM_MAX_LINE_LENGTH) {
					data.emplace_back(current_line);
					current_line.clear();
					current_line = entry;
				}
				else if (current_line.empty()) {
					current_line = entry;
				}
				else {
					current_line += " " + entry;
				}
			}

			data.emplace_back(current_line);
			current_line.clear();
		}

		std::vector<std::string> strings;
		const char* const delim = "\n";
		std::ostringstream imploded;
		std::copy(data.begin(), data.end(), std::ostream_iterator<std::string>(imploded, delim));

		return header + imploded.str();
	}

}