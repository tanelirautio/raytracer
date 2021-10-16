#ifndef __RT_PLANE_HPP__
#define __RT_PLANE_HPP__

#include "rtShape.hpp"

namespace rt {
	class Ray;
	struct Point;
	class Plane : public Shape {
		public:
			Plane() : Shape(Type::PLANE) {};
			virtual Vector local_normal_at(const Point& p) const override;
			virtual std::vector<Intersection> local_intersect(const Ray& r) const override;
		private:
	};
}

#endif