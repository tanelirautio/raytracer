#ifndef __RT_MATERIAL_HPP__
#define __RT_MATERIAL_HPP__

#include "rtDefs.hpp"
#include "rtTuple.hpp"

namespace rt {
	class PointLight;

	struct Material {
		Material() {
			color = { 1,1,1 };
			ambient = 0.1f;
			diffuse = 0.9f;
			specular = 0.9f;
			shininess = 200.f;
		}
		Color color;
		f32 ambient;
		f32 diffuse;
		f32 specular;
		f32 shininess;
	};

	Color lighting(const Material& material, const PointLight& light, const Point& position, const Vector& eyev, const Vector& normalv);

	bool operator==(const Material& lhs, const Material& rhs);
}

#endif