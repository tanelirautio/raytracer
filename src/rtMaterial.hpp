#ifndef __RT_MATERIAL_HPP__
#define __RT_MATERIAL_HPP__

#include "rtDefs.hpp"
#include "rtTuple.hpp"

namespace rt {
	class Material {
		public:
			Material() {
				set_default();
			}
			rt::Color color() { return m_color; }
			f32 ambient() { return m_ambient; }
			f32 diffuse() { return m_diffuse; }
			f32 specular() { return m_specular; }
			f32 shininess() { return m_shininess; }
		private:
			void set_default() {
				m_color = { 1,1,1 };
				m_ambient = 0.1f;
				m_diffuse = 0.9f;
				m_specular = 0.9f;
				m_shininess = 200.f;
			}

			rt::Color m_color;
			f32 m_ambient;
			f32 m_diffuse;
			f32 m_specular;
			f32 m_shininess;
	};
}

#endif