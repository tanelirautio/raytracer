#include "rtTuple.hpp"
#include "rtFile.hpp"
#include "rtCanvas.hpp"
#include "rtLog.hpp"

std::vector<std::string> split_string_by_newline(const std::string& str)
{
	auto result = std::vector<std::string>{};
	auto ss = std::stringstream{ str };

	for (std::string line; std::getline(ss, line, '\n');)
		result.push_back(line);

	return result;
}

int main() {

	rt::Canvas c(10, 2);
	rt::Color c1(1.0f, 0.8f, 0.6f);

	for (int y = 0; y < c.get_height(); y++) {
		for (int x = 0; x < c.get_width(); x++) {
			c.write_pixel(x, y, c1);
		}
	}

	auto data = c.canvas_to_ppm();
	auto lines = split_string_by_newline(data);

	for (auto& line : lines) {
		LOG("%s", line.c_str());
	}

	return 0;
}