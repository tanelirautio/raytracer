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

}