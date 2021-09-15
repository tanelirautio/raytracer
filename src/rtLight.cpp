#include "rtLight.hpp"
#include "rtUtil.hpp"

namespace rt {

	bool operator==(const PointLight& lhs, const PointLight& rhs) {
		return lhs.intensity() == rhs.intensity() &&
			lhs.position() == rhs.position();
	}
}