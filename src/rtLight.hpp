#ifndef __RT_LIGHT_HPP__
#define __RT_LIGHT_HPP__

#include "rtTuple.hpp"

namespace rt {
	class PointLight {
		public:
			PointLight(const rt::Point& position, const rt::Color& intensity) {
				m_position = position;
				m_intensity = intensity;
			}
			rt::Point position() const { return m_position; }
			rt::Color intensity() const { return m_intensity; }
		private:
			rt::Point m_position;
			rt::Color m_intensity;
	};
 }

#endif