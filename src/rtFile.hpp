#ifndef __RT_FILE_HPP__
#define __RT_FILE_HPP__

#include <string>

namespace rt {
	std::string read_file(const std::string& filename);
	void write_file(const std::string& filename, const std::string& data);
}
#endif
