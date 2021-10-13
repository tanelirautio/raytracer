#ifndef __RT_PRIMITIVE_HPP__
#define __RT_PRIMITIVE_HPP__

#include "rtDefs.hpp"
#include "rtMaterial.hpp"
#include "rtMatrix.hpp"
#include "rtRay.hpp"
#include <optional>
#include <vector>

namespace rt {
	struct Intersection;
	struct Vector;
	struct Point;

	/*
	class IShape {
		public:
			virtual std::vector<Intersection> intersect(const Ray& ray) const = 0;

	};
	*/

	class Shape {
		public:
			enum class Type {
				SPHERE,
				CUBE,
				UNKNOWN
			};
			Shape(Type type) { 
				ID++;
				m_type = type;
				m_transform = get_identity_matrix4();
			}
			virtual ~Shape() = default;

			i32 id() const { return ID; }

			const Matrix& transform() const { return m_transform; }
			Matrix& transform() { return m_transform; }

			const Material& material() const { return m_material; }
			Material& material() { return m_material; }

			const Type& type() const { return m_type; }
			Type& type() { return m_type; }

			virtual std::vector<Intersection> intersect(const Ray& ray) const;

			virtual Vector normal_at(const Point& world_point) const = 0;
			virtual std::vector<Intersection> local_intersect(const Ray& local_ray) const = 0;
		protected:
			Material m_material;
			Matrix m_transform;
		private:
			Type m_type = Type::UNKNOWN;

			static i32 ID;
	};

	bool operator==(const Shape& lhs, const Shape& rhs);

	// Dummy class for unit testing purposes
	class TestShape : public Shape {
		public:
			TestShape() : Shape(Type::UNKNOWN) {}
			Vector normal_at(const Point& world_point) const override;
			std::vector<Intersection> local_intersect(const Ray& local_ray) const override;
		
			Ray get_saved_ray() { return m_saved_ray; }
		private:
			mutable Ray m_saved_ray;
	};
}

#endif