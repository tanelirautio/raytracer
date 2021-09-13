#ifndef __RT_MATERIAL_HPP__
#define __RT_MATERIAL_HPP__

#include "rtDefs.hpp"
#include "rtTuple.hpp"

namespace rt {
	class PointLight;
	class Material {
		public:
			Material() {
				set_default();
			}
			Color color() const { return m_color; }
			f32 ambient() const { return m_ambient; }
			f32 diffuse() const { return m_diffuse; }
			f32 specular() const { return m_specular; }
			f32 shininess() const { return m_shininess; }

			void color(Color value) { m_color = value; }
			void ambient(f32 value) { m_ambient = value; }
			void diffuse(f32 value) { m_diffuse = value; }
			void specular(f32 value) { m_specular = value; }
			void shininess(f32 value) { m_shininess = value; }
		private:
			void set_default() {
				m_color = { 1,1,1 };
				m_ambient = 0.1f;
				m_diffuse = 0.9f;
				m_specular = 0.9f;
				m_shininess = 200.f;
			}

			Color m_color;
			f32 m_ambient;
			f32 m_diffuse;
			f32 m_specular;
			f32 m_shininess;
	};

	Color lighting(const Material& material, const PointLight& light, const Point& position, const Vector& eyev, const Vector& normalv);

	bool operator==(const Material& lhs, const Material& rhs);
}

#endif