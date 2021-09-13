#include "rtWorld.hpp"

namespace rt {


	World get_default_world() {
		World w;
		w.create_default();
		return w;

	}
}