#include "appScene.hpp"

#include "rtMain.hpp"

#include <stdexcept>
#include <utility>

namespace app {
	namespace {
		constexpr std::string_view SIMPLE_SPHERE = "simple_sphere";
		constexpr std::string_view BASIC_SPHERES = "basic_spheres";
		constexpr std::string_view PATTERN_SPHERES = "pattern_spheres";

		Scene make_simple_sphere(i32 width, i32 height) {
			rt::World world;

			auto& sphere = world.emplace_object<rt::Sphere>();
			sphere.material().color = { 1, 0.2f, 1 };

			rt::PointLight light({ -10, 10, -10 }, { 1, 1, 1 });
			world.set_light(std::make_shared<rt::PointLight>(light));

			rt::Camera camera(width, height, (f32)(M_PI / 3.f));
			camera.transform() = rt::view_transform({ 0, 0, -5 }, { 0, 0, 0 }, { 0, 1, 0 });

			return Scene(std::string(SIMPLE_SPHERE), std::move(world), std::move(camera));
		}

		Scene make_basic_spheres(i32 width, i32 height) {
			rt::World world;

			auto& floor = world.emplace_object<rt::Plane>();
			floor.transform() = rt::translation(0, 0.5f, 0);
			floor.transform() = rt::scaling(10, 0.01f, 10);
			floor.material() = rt::Material();
			floor.material().color = rt::Color(0.8f, 0.1f, 0.1f);
			floor.material().specular = 0;

			auto& middle = world.emplace_object<rt::Sphere>();
			middle.transform() = rt::translation(-0.5f, 1, 0.5f);
			middle.material() = rt::Material();
			middle.material().color = { 0.1f, 0.2f, 0.5f };
			middle.material().diffuse = 0.7f;
			middle.material().specular = 1.0f;

			auto& right = world.emplace_object<rt::Sphere>();
			right.transform() = rt::translation(1.5f, 0.5f, -0.5f) * rt::scaling(0.5f, 0.5f, 0.5f);
			right.material().color = { 0.5f, 1, 0.1f };
			right.material().diffuse = 0.7f;
			right.material().specular = 0.3f;

			auto& left = world.emplace_object<rt::Sphere>();
			left.transform() = rt::translation(-1.5f, 0.33f, -0.75f) * rt::scaling(0.33f, 0.33f, 0.33f);
			left.material() = rt::Material();
			left.material().color = { 1, 0.8f, 0.1f };
			left.material().diffuse = 0.7f;
			left.material().specular = 0.3f;

			rt::PointLight light({ -10, 10, -10 }, { 1, 1, 1 });
			world.set_light(std::make_shared<rt::PointLight>(light));

			rt::Camera camera(width, height, (f32)(M_PI / 3.f));
			camera.transform() = rt::view_transform({ 0, 1.5f, -5 }, { 0, 1, 0 }, { 0, 1, 0 });

			return Scene(std::string(BASIC_SPHERES), std::move(world), std::move(camera));
		}

		Scene make_pattern_spheres(i32 width, i32 height) {
			rt::World world;

			auto& floor = world.emplace_object<rt::Plane>();
			floor.transform() = rt::translation(0, 0.5f, 0);
			floor.transform() = rt::scaling(10, 0.01f, 10);
			floor.material() = rt::Material();
			floor.material().color = rt::Color(0.8f, 0.1f, 0.1f);
			floor.material().specular = 0;
			floor.material().pattern = std::make_shared<rt::CheckerPattern>(rt::NAVY_BLUE, rt::SKY_BLUE);
			floor.material().pattern.get()->transform() = rt::scaling(0.02f, 0.02f, 0.02f);

			auto& middle = world.emplace_object<rt::Sphere>();
			middle.transform() = rt::translation(-0.5f, 1, 0.5f);
			middle.material() = rt::Material();
			middle.material().color = { 0.1f, 0.2f, 0.5f };
			middle.material().diffuse = 0.7f;
			middle.material().specular = 1.0f;
			middle.material().pattern = std::make_shared<rt::RingPattern>(rt::OLIVE, rt::DARK_GREEN);
			middle.material().pattern.get()->transform() = rt::scaling(0.1f, 0.1f, 0.1f) * rt::rotation_x((f32)M_PI / 2.f);

			auto& right = world.emplace_object<rt::Sphere>();
			right.transform() = rt::translation(1.5f, 0.5f, -0.5f) * rt::scaling(0.5f, 0.5f, 0.5f);
			right.material().color = { 0.5f, 1, 0.1f };
			right.material().diffuse = 0.7f;
			right.material().specular = 0.3f;
			right.material().pattern = std::make_shared<rt::PerlinPattern>(rt::SILVER, rt::DEEP_PINK);
			right.material().pattern.get()->transform() = rt::scaling(0.25f, 0.25f, 0.25f);

			auto& left = world.emplace_object<rt::Sphere>();
			left.transform() = rt::translation(-1.5f, 0.33f, -0.75f) * rt::scaling(0.33f, 0.33f, 0.33f);
			left.material() = rt::Material();
			left.material().color = { 1, 0.8f, 0.1f };
			left.material().diffuse = 0.7f;
			left.material().specular = 0.3f;
			left.material().pattern = std::make_shared<rt::RingPattern>(rt::WHITE, rt::HOT_PINK);
			left.material().pattern.get()->transform() = rt::scaling(0.1f, 0.1f, 0.1f) * rt::rotation_x((f32)M_PI / 2.f);

			rt::PointLight light({ -10, 10, -10 }, { 1, 1, 1 });
			world.set_light(std::make_shared<rt::PointLight>(light));

			rt::Camera camera(width, height, (f32)(M_PI / 3.f));
			camera.transform() = rt::view_transform({ 0, 1.5f, -5 }, { 0, 1, 0 }, { 0, 1, 0 });

			return Scene(std::string(PATTERN_SPHERES), std::move(world), std::move(camera));
		}

		struct SceneFactory {
			std::string_view name;
			Scene(*create)(i32 width, i32 height);
		};

		const std::vector<SceneFactory>& scene_registry() {
			static const std::vector<SceneFactory> registry{
				{ SIMPLE_SPHERE, make_simple_sphere },
				{ BASIC_SPHERES, make_basic_spheres },
				{ PATTERN_SPHERES, make_pattern_spheres },
			};
			return registry;
		}
	}

	Scene::Scene(std::string scene_name, rt::World scene_world, rt::Camera scene_camera)
		: name(std::move(scene_name)), world(std::move(scene_world)), camera(std::move(scene_camera)) {}

	std::string_view default_scene_name() {
		return PATTERN_SPHERES;
	}

	std::vector<std::string_view> scene_names() {
		std::vector<std::string_view> names;
		for (const auto& scene : scene_registry()) {
			names.push_back(scene.name);
		}
		return names;
	}

	Scene make_scene(std::string_view name, i32 width, i32 height) {
		for (const auto& scene : scene_registry()) {
			if (scene.name == name) {
				return scene.create(width, height);
			}
		}

		throw std::invalid_argument("Unknown scene: " + std::string(name));
	}
}
