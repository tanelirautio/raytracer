#include "appScene.hpp"

#include "rtMain.hpp"

#include <stdexcept>
#include <utility>

namespace app {
	namespace {
		constexpr std::string_view SIMPLE_SPHERE = "simple_sphere";
		constexpr std::string_view BASIC_SPHERES = "basic_spheres";
		constexpr std::string_view PATTERN_SPHERES = "pattern_spheres";
		constexpr std::string_view REFLECTIVE_PLANE = "reflective_plane";
		constexpr std::string_view MUTUALLY_REFLECTIVE_SURFACES = "mutually_reflective_surfaces";

		Scene make_simple_sphere(i32 width, i32 height) {
			rt::World world;

			auto& sphere = world.emplace_object<rt::Sphere>();
			sphere.material().color = { 1, 0.2f, 1 };

			rt::PointLight light({ -10, 10, -10 }, { 1, 1, 1 });
			world.set_light(light);

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
			world.set_light(light);

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
			world.set_light(light);

			rt::Camera camera(width, height, (f32)(M_PI / 3.f));
			camera.transform() = rt::view_transform({ 0, 1.5f, -5 }, { 0, 1, 0 }, { 0, 1, 0 });

			return Scene(std::string(PATTERN_SPHERES), std::move(world), std::move(camera));
		}

		Scene make_reflective_plane(i32 width, i32 height) {
			rt::World world;

			auto& large_back = world.emplace_object<rt::Sphere>();
			large_back.transform() = rt::translation(0.0f, 1.15f, 2.0f) * rt::scaling(1.15f, 1.15f, 1.15f);
			large_back.material().diffuse = 0.65f;
			large_back.material().specular = 0.6f;
			large_back.material().pattern = std::make_shared<rt::RingPattern>(rt::WHITE, rt::NAVY_BLUE);
			large_back.material().pattern->transform() = rt::scaling(0.18f, 0.18f, 0.18f) * rt::rotation_x((f32)M_PI / 2.f);

			auto& left_front = world.emplace_object<rt::Sphere>();
			left_front.transform() = rt::translation(-1.9f, 0.55f, -0.8f) * rt::scaling(0.55f, 0.55f, 0.55f);
			left_front.material().diffuse = 0.7f;
			left_front.material().specular = 0.4f;

			auto left_front_stripes = std::make_shared<rt::StripedPattern>(rt::ORANGE_RED, rt::YELLOW);
			left_front_stripes->transform() =
				rt::scaling(0.18f, 0.18f, 0.18f) *
				rt::rotation_z((f32)M_PI / 5.f);

			left_front.material().pattern = std::make_shared<rt::PerturbedPattern>(
				left_front_stripes,
				0.12f);

			auto& right_front = world.emplace_object<rt::Sphere>();
			right_front.transform() = rt::translation(1.7f, 0.45f, -1.1f) * rt::scaling(0.45f, 0.45f, 0.45f);
			right_front.material().diffuse = 0.7f;
			right_front.material().specular = 0.7f;
			right_front.material().pattern = std::make_shared<rt::CheckerPattern>(rt::SILVER, rt::DEEP_PINK);
			right_front.material().pattern->transform() = rt::scaling(0.22f, 0.22f, 0.22f);

			auto& left_mid = world.emplace_object<rt::Sphere>();
			left_mid.transform() = rt::translation(-1.2f, 0.85f, 1.0f) * rt::scaling(0.85f, 0.85f, 0.85f);
			left_mid.material().diffuse = 0.65f;
			left_mid.material().specular = 0.5f;
			left_mid.material().pattern = std::make_shared<rt::GradientPattern>(rt::SKY_BLUE, rt::DARK_GREEN);
			left_mid.material().pattern->transform() = rt::scaling(1.4f, 1.4f, 1.4f);

			auto& right_mid = world.emplace_object<rt::Sphere>();
			right_mid.transform() = rt::translation(1.35f, 0.7f, 0.75f) * rt::scaling(0.7f, 0.7f, 0.7f);
			right_mid.material().diffuse = 0.75f;
			right_mid.material().specular = 0.35f;
			right_mid.material().color = rt::HOT_PINK;

			auto& tiny_center = world.emplace_object<rt::Sphere>();
			tiny_center.transform() = rt::translation(0.15f, 0.28f, -1.65f) * rt::scaling(0.28f, 0.28f, 0.28f);
			tiny_center.material().diffuse = 0.6f;
			tiny_center.material().specular = 0.9f;
			tiny_center.material().shininess = 300.f;
			tiny_center.material().color = rt::YELLOW;

			auto& floor = world.emplace_object<rt::Plane>();
			floor.material().color = rt::Color(0.32f, 0.34f, 0.36f);
			floor.material().ambient = 0.04f;
			floor.material().diffuse = 0.35f;
			floor.material().specular = 0.8f;
			floor.material().shininess = 300.f;
			floor.material().reflective = 0.45f;

			rt::PointLight light({ -5, 8, -6 }, { 1, 1, 1 });
			world.set_light(light);

			rt::Camera camera(width, height, (f32)(M_PI / 3.2f));
			camera.transform() = rt::view_transform(
				{ 0, 2.2f, -6.5f },
				{ 0, 0.75f, 0.35f },
				{ 0, 1, 0 });

			return Scene(std::string(REFLECTIVE_PLANE), std::move(world), std::move(camera));
		}

		Scene make_mutually_reflective_surfaces(i32 width, i32 height) {
			rt::World world;

			auto& center = world.emplace_object<rt::Sphere>();
			center.transform() = rt::translation(0.f, 0.55f, 0.f) * rt::scaling(0.5f, 0.5f, 0.5f);
			center.material().diffuse = 0.6f;
			center.material().specular = 0.9f;
			center.material().shininess = 300.f;
			center.material().color = rt::HOT_PINK;

			auto& left = world.emplace_object<rt::Sphere>();
			left.transform() = rt::translation(-1.1f, 0.35f, -0.45f) * rt::scaling(0.35f, 0.35f, 0.35f);
			left.material().diffuse = 0.7f;
			left.material().specular = 0.5f;
			left.material().shininess = 200.f;
			left.material().color = rt::SKY_BLUE;

			auto& right = world.emplace_object<rt::Sphere>();
			right.transform() = rt::translation(0.95f, 0.28f, -1.15f) * rt::scaling(0.28f, 0.28f, 0.28f);
			right.material().diffuse = 0.7f;
			right.material().specular = 0.6f;
			right.material().shininess = 250.f;
			right.material().color = rt::YELLOW;

			auto& floor = world.emplace_object<rt::Plane>();
			floor.material().color = rt::Color(0.32f, 0.34f, 0.36f);
			floor.material().ambient = 0.08f;
			floor.material().diffuse = 0.35f;
			floor.material().specular = 0.8f;
			floor.material().shininess = 300.f;
			floor.material().reflective = 0.65f;
			floor.material().pattern = std::make_shared<rt::CheckerPattern>(rt::WHITE, rt::BLACK);
			floor.material().pattern->transform() = rt::scaling(0.5f, 0.5f, 0.5f);

			auto& ceiling = world.emplace_object<rt::Plane>();
			ceiling.transform() = rt::translation(0, 1.8f, 0);
			ceiling.material().color = rt::Color(0.26f, 0.28f, 0.30f);
			ceiling.material().ambient = 0.08f;
			ceiling.material().diffuse = 0.35f;
			ceiling.material().specular = 0.8f;
			ceiling.material().shininess = 300.f;
			ceiling.material().reflective = 0.65f;

			rt::PointLight light({ -3.5f, 1.35f, -4.0f }, { 1, 1, 1 });
			world.set_light(light);

			rt::Camera camera(width, height, (f32)(M_PI / 2.6f));
			camera.transform() = rt::view_transform(
				{ 0, 0.9f, -4.8f },
				{ 0, 0.75f, 0.0f },
				{ 0, 1, 0 });

			return Scene(std::string(MUTUALLY_REFLECTIVE_SURFACES), std::move(world), std::move(camera));
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
				{ REFLECTIVE_PLANE, make_reflective_plane },
				{ MUTUALLY_REFLECTIVE_SURFACES, make_mutually_reflective_surfaces }
			};
			return registry;
		}
	}

	Scene::Scene(std::string scene_name, rt::World scene_world, rt::Camera scene_camera)
		: name(std::move(scene_name)), world(std::move(scene_world)), camera(std::move(scene_camera)) {}

	std::string_view default_scene_name() {
		return MUTUALLY_REFLECTIVE_SURFACES;
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
