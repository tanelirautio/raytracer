#include "rtFile.hpp"

#include <fstream>
#include <sstream>

namespace rt {

	std::string read_file(const std::string& filename) {
		std::ifstream in(filename);
		std::stringstream buffer;
		buffer << in.rdbuf();
		return buffer.str();
	}

	void write_file(const std::string& filename, const std::string& data) {
		std::ofstream out(filename);
		out << data << std::endl;
		out.close();
	}

}
