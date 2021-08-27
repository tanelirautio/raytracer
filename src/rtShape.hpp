#ifndef __RT_PRIMITIVE_HPP__
#define __RT_PRIMITIVE_HPP__

#include "rtDefs.hpp"
#include <string>
#include <map>

namespace rt {
	class Shape {
		public:
			Shape() { ID++; }
			virtual ~Shape() = default;
			i32 id() const { return ID; }
		private:
			static i32 ID;
	};

	bool operator==(const Shape& lhs, const Shape& rhs);
}

#endif