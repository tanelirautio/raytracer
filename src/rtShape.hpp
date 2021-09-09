#ifndef __RT_PRIMITIVE_HPP__
#define __RT_PRIMITIVE_HPP__

#include "rtDefs.hpp"
//#include <string>
//#include <map>
#include <optional>
#include <vector>

namespace rt {
	struct Intersection;
	class Ray;
	class Vector;
	class Point;
	class Material;
	class Shape {
		public:
			Shape() { ID++; }
			virtual ~Shape() = default;
			i32 id() const { return ID; }

			virtual Material get_material() const = 0;
			virtual void set_material(const Material& m) = 0;

			virtual std::vector<Intersection> intersect(const Ray& ray) const = 0;
			virtual std::optional<Intersection> hit(std::vector<Intersection>& intersections) const = 0;
			virtual Vector normal_at(const Point& world_point) const = 0;
		private:
			static i32 ID;
	};

	bool operator==(const Shape& lhs, const Shape& rhs);
}

#endif