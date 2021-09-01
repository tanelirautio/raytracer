#ifndef __RT_PRIMITIVE_HPP__
#define __RT_PRIMITIVE_HPP__

#include "rtDefs.hpp"
#include <string>
#include <map>
#include <optional>
#include <vector>

namespace rt {
	struct Intersection;
	class Shape {
		public:
			Shape() { ID++; }
			virtual ~Shape() = default;
			i32 id() const { return ID; }

			virtual std::optional<Intersection> hit(std::vector<Intersection>& intersections) = 0;
		private:
			static i32 ID;
	};

	bool operator==(const Shape& lhs, const Shape& rhs);
}

#endif