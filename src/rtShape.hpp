#ifndef __RT_PRIMITIVE_HPP__
#define __RT_PRIMITIVE_HPP__

#include "rtDefs.hpp"
#include "rtMaterial.hpp"
#include "rtMatrix.hpp"
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
			enum class Type {
				Sphere,
				Cube,
				Unknown
			};
			Shape(Type type) { 
				ID++;
				m_type = type;
			}
			virtual ~Shape() = default;

			i32 id() const { return ID; }

			//Matrix get_transform() const;
			const Matrix& transform() const { return m_transform; }
			Matrix& transform() { return m_transform; }

			//void set_transform(const Matrix & m);

			const Material& material() const { return m_material; }
			Material& material() { return m_material; }

			Type get_type() const { return m_type; }

			virtual std::vector<Intersection> intersect(const Ray& ray) const;
			virtual std::optional<Intersection> hit(std::vector<Intersection>& intersections) const;
			virtual Vector normal_at(const Point& world_point) const;
		protected:
			Material m_material;
			Matrix m_transform;
		private:
			Type m_type = Type::Unknown;

			static i32 ID;
	};

	bool operator==(const Shape& lhs, const Shape& rhs);
}

#endif