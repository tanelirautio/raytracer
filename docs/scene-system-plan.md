# Scene System Plan

## Goal

Make it quick to create and switch between scenes without adding a new app-specific class for every image.

## Todo

1. Create a `Scene` type and scene registry/factory. Done.
   - Keep the app runner generic.
   - Move current `Sphere3` scene construction behind a named scene factory.
   - Allow choosing scenes by name from app code.
2. Add lightweight C++ scene builder helpers.
   - Reduce repeated material, transform, camera, and light setup code.
   - Keep the scene descriptions in C++ while the ray tracer vocabulary is still changing.
3. Add JSON or TOML scene loading later.
   - Wait until shapes, materials, patterns, and transforms are stable enough to describe as data.
   - Prefer TOML for hand-authored scene files if comments/readability matter most.

## Current Scope

Item 1 is implemented. Keep the next implementation pass focused on item 2.

## Registered Scenes

- `simple_sphere`
- `basic_spheres`
- `pattern_spheres`
