#ifndef __RT_LIGHT_HPP__
#define __RT_LIGHT_HPP__

#include "rtTuple.hpp"

namespace rt {
	class PointLight {
		public:
			PointLight(const Point& position, const Color& intensity) {
				m_position = position;
				m_intensity = intensity;
			}
			Point position() const { return m_position; }
			Color intensity() const { return m_intensity; }
		private:
			Point m_position;
			Color m_intensity;
	};

	bool operator==(const PointLight& lhs, const PointLight& rhs);

 }

#endif