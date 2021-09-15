#include "rtShape.hpp"
#include "rtTuple.hpp"
#include "rtIntersection.hpp"
#include <optional>

namespace rt {
	i32 Shape::ID = 0;

	Matrix Shape::get_transform() const { 
		return m_transform; 
	}

	void Shape::set_transform(const Matrix& m) { 
		m_transform = m; 
	}

	Material Shape::get_material() const { 
		return m_material; 
	}

	void Shape::set_material(const Material& m) { 
		m_material = m; 
	}

	std::vector<Intersection> Shape::intersect(const Ray& ray) const {
		return std::vector<Intersection>(); 
	}

	std::optional<Intersection> Shape::hit(std::vector<Intersection>& intersections) const { 
		return std::nullopt; 
	}

	Vector Shape::normal_at(const Point& world_point) const { 
		return Vector(); 
	}

	bool operator==(const Shape& lhs, const Shape& rhs) {
		return lhs.id() == rhs.id();
	}
}
