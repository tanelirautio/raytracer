#ifndef __RT_PATTERN_HPP__
#define __RT_PATTERN_HPP__

#include "rtMatrix.hpp"
#include "rtTuple.hpp"
#include <memory>

namespace rt {
	class Shape;
	class Matrix;
	struct Color;
	class Pattern {
		public:
			enum class Type {
				STRIPE,
				GRADIENT,
				RING,
				CHECKER,
				UNKNOWN
			};

			Pattern(Type type) {
				m_type = type;
				m_transform = get_identity_matrix4();
			}
			virtual ~Pattern() = default;
			
			const Matrix& transform() const { return m_transform; }
			Matrix& transform() { return m_transform; }

			Color pattern_at_shape(const Shape& shape, const Point& p) const;
			virtual Color pattern_at(const Point& p) const = 0;

			auto clone() const { return std::unique_ptr<Pattern>(clone_impl()); }
		protected:
			virtual Pattern* clone_impl() const = 0;
		private:
			Matrix m_transform;
			Type m_type;
	};

	// Dummy class for unit testing purposes
	class TestPattern : public Pattern {
		public:
			TestPattern() : Pattern(Type::UNKNOWN) {}
			Color pattern_at(const Point& p) const final override {
				return Color(p.x, p.y, p.z);
			}
		protected:
			virtual TestPattern* clone_impl() const override { return new TestPattern(*this); };
	};
}

#endif