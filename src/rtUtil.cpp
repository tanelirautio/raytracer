#include "rtUtil.hpp"

#include "rtDefs.hpp"
#include <cmath>
#include <sstream>

namespace rt {

	bool equal(f32 a, f32 b) {
		if (std::abs(a - b) < EPSILON) {
			return true;
		}
		return false;
	}

    std::string format_duration(std::chrono::milliseconds ms) {
        using namespace std::chrono;
        auto secs = duration_cast<seconds>(ms);
        ms -= duration_cast<milliseconds>(secs);
        auto mins = duration_cast<minutes>(secs);
        secs -= duration_cast<seconds>(mins);
        auto hour = duration_cast<hours>(mins);
        mins -= duration_cast<minutes>(hour);

        std::stringstream ss;
        ss << hour.count() << " Hours : " << mins.count() << " Minutes : " << secs.count() << " Seconds : " << ms.count() << " Milliseconds";
        return ss.str();
    }

    std::string format_minute_seconds(std::chrono::milliseconds ms) {
        using namespace std::chrono;
        auto secs = duration_cast<seconds>(ms);   // Get total seconds
        ms -= duration_cast<milliseconds>(secs);  // Remove milliseconds from ms
        auto mins = duration_cast<minutes>(secs); // Get total minutes
        secs -= duration_cast<seconds>(mins);     // Get remaining seconds

        std::stringstream ss;
        ss << mins.count() << " Minutes : " << secs.count() << " Seconds";
        return ss.str();
    }

    Color lerp_color(const Color& a, const Color& b, f32 t) {
        t = clamp(t, 0.0f, 1.0f);
        return a * (1 - t) + b * t;
    }

    float clamp(f32 x, f32 minval, f32 maxval) {
        return std::min(std::max(x, minval), maxval);
    }

    f32 lerp(f32 a, f32 b, f32 t) {
        return (1 - t) * a + t * b;
    }
}