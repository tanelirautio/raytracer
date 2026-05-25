#ifndef __RT_SHAPE_HPP__
#define __RT_SHAPE_HPP__

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

	class Shape {
		public:
			enum class Type {
				SPHERE,
				PLANE,
				CUBE,
				UNKNOWN
			};
			Shape(Type type) : m_transform(get_identity_matrix4()), m_type(type), m_id(++NEXT_ID) {}
			Shape(const Shape& other)
				: m_material(other.m_material), m_transform(other.m_transform), m_type(other.m_type), m_id(++NEXT_ID) {}
			Shape& operator=(const Shape& other) {
				if (this != &other) {
					m_material = other.m_material;
					m_transform = other.m_transform;
					m_type = other.m_type;
				}
				return *this;
			}
			virtual ~Shape() = default;

			i32 id() const { return m_id; }

			const Matrix& transform() const { return m_transform; }
			Matrix& transform() { return m_transform; }

			const Material& material() const { return m_material; }
			Material& material() { return m_material; }

			const Type& type() const { return m_type; }
			Type& type() { return m_type; }

			std::vector<Intersection> intersect(const Ray& ray) const;
			Vector normal_at(const Point& world_point) const;

			virtual Vector local_normal_at(const Point& world_point) const = 0;
			virtual std::vector<Intersection> local_intersect(const Ray& local_ray) const = 0;
		protected:
			Material m_material;
			Matrix m_transform;
		private:
			Type m_type = Type::UNKNOWN;
			i32 m_id = 0;

			static i32 NEXT_ID;
	};

	bool operator==(const Shape& lhs, const Shape& rhs);

	// Dummy class for unit testing purposes
	class TestShape : public Shape {
		public:
			TestShape() : Shape(Type::UNKNOWN) {}
			Vector local_normal_at(const Point& world_point) const override;
			std::vector<Intersection> local_intersect(const Ray& local_ray) const override;
		
			Ray get_saved_ray() { return m_saved_ray; }
		private:
			mutable Ray m_saved_ray;
	};
}

#endif
