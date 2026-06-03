#ifndef __APP_SCENE_HPP__
#define __APP_SCENE_HPP__

#include "rtCamera.hpp"
#include "rtWorld.hpp"

#include <string>
#include <string_view>
#include <vector>

namespace app {
	struct Scene {
		Scene(std::string scene_name, rt::World scene_world, rt::Camera scene_camera);

		std::string name;
		rt::World world;
		rt::Camera camera;
	};

	std::string_view default_scene_name();
	std::vector<std::string_view> scene_names();
	Scene make_scene(std::string_view name, i32 width, i32 height);
}

#endif
