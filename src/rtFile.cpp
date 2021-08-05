#include "rtFile.hpp"

#include <fstream>
#include <sstream>

namespace rt {

	std::string File::read(const std::string& filename) {
		std::ifstream in(filename);
		std::stringstream buffer;
		buffer << in.rdbuf();
		return buffer.str();
	}

	void File::write(const std::string& filename, std::string& data) {
		std::ofstream out(filename);
		out << data << std::endl;
		out.close();
	}

}
