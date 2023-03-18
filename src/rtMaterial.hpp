#ifndef __RT_MATERIAL_HPP__
#define __RT_MATERIAL_HPP__

#include "rtDefs.hpp"
#include "rtTuple.hpp"
#include "rtStripedPattern.hpp"
#include <memory>

namespace rt {
	class PointLight;
    class Shape;

    struct Material {
        Material() : color({ 1,1,1 }), ambient(0.1f), diffuse(0.9f), specular(0.9f), shininess(200.f), pattern(nullptr) {}
        ~Material() = default;

        Color color;
        f32 ambient;
        f32 diffuse;
        f32 specular;
        f32 shininess;
        std::shared_ptr<Pattern> pattern;
    };

	Color lighting(
        const Material& material, 
        const Shape& object,
        const PointLight& light, 
        const Point& position, 
        const Vector& eyev, 
        const Vector& normalv, 
        bool in_shadow = false);

	bool operator==(const Material& lhs, const Material& rhs);
}

#endif