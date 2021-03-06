#include "rtMaterial.hpp"
#include "rtLight.hpp"

namespace rt {

	bool operator==(const Material& lhs, const Material& rhs) {
		if (lhs.color == rhs.color &&
			lhs.ambient == rhs.ambient &&
			lhs.diffuse == rhs.diffuse &&
			lhs.specular == rhs.specular &&
			lhs.shininess == rhs.shininess) {
			return true;
		}
		return false;
	}

	Color lighting(const Material& material, const PointLight& light, const Point& point, const Vector& eyev, const Vector& normalv, bool in_shadow) {
		// initialize the three different contibutions
		Color ambient;
		Color diffuse;
		Color specular;

		// combine the surface color with the light's color/intensity
		auto effective_color = material.color * light.intensity();

		// find the direction to light source
		Vector lightv = (light.position() - point).normalize();

		// compute the ambient contribution
		ambient = effective_color * material.ambient;

		// if in shadow, just return ambient color
		if (in_shadow) {
			return ambient;
		}

		// light_dot_normal represents the cosine of the angle between the
		// light vector and the normal vector. A negative number means the
		// light is on the other side of the surface.
		auto light_dot_normal = lightv.dot(normalv);
		if (light_dot_normal < 0) {
			diffuse = get_color_black();
			specular = get_color_black();
		}
		else {
			// compute the diffuse contribution
			diffuse = effective_color * material.diffuse * light_dot_normal;

			// reflect_dot_eye represents the cosine of the angle between the
			// reflection vector and the eye vector. A negative number means the
			// light reflects away from the eye.
			Vector reflectv = -lightv.reflect(normalv);
			auto reflect_dot_eye = reflectv.dot(eyev);
			if (reflect_dot_eye <= 0) {
				specular = get_color_black();
			}
			else {
				// compute the specular contribution
				auto factor = pow(reflect_dot_eye, material.shininess);
				specular = light.intensity() * material.specular * factor;
			}
		}

		// add the three contibutions together for final shading
		return ambient + diffuse + specular;
	}
}