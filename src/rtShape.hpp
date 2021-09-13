#ifndef __RT_PRIMITIVE_HPP__
#define __RT_PRIMITIVE_HPP__

#include "rtDefs.hpp"
#include "rtMaterial.hpp"
#include <optional>
#include <vector>

namespace rt {
	struct Intersection;
	class Ray;
	class Vector;
	class Point;

	class IShape {
		public:
			virtual std::vector<Intersection> intersect(const Ray& ray) const = 0;
			virtual std::optional<Intersection> hit(std::vector<Intersection>& intersections) const = 0;
			virtual Vector normal_at(const Point& world_point) const = 0;
	};
	
	class Shape : public IShape {
		public:
			Shape() { ID++; }
			virtual ~Shape() = default;
			i32 id() const { return ID; }

			Material get_material() const { return m_material; }
			void set_material(const Material& m) { m_material = m; }

			virtual std::vector<Intersection> intersect(const Ray& ray) const;
			virtual std::optional<Intersection> hit(std::vector<Intersection>& intersections) const;
			virtual Vector normal_at(const Point& world_point) const;
		private:
			static i32 ID;

			Material m_material;
	};

	bool operator==(const Shape& lhs, const Shape& rhs);
}

#endif