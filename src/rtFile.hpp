#ifndef __RT_FILE_HPP__
#define __RT_FILE_HPP__

#include <string>

namespace rt {
	class File {
		public:
			static std::string read(const std::string& filename);
			static void write(const std::string& filename, const std::string& data);
		private:
			File() = delete;
	};

}
#endif
