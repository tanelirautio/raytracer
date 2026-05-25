# Window Backend Migration Spec

## Summary

Replace the current vendored SDL2 windowing setup with a package-managed backend and remove hardcoded SDK embedding from the Visual Studio project files.

Recommended target: `SDL3` and `SDL3_ttf` via `vcpkg` in manifest mode.

## Motivation

- Current app build depends on vendored SDL2 binaries under `lib/windows/`.
- `project/windows/app.vcxproj` contains hardcoded include paths, library paths, linker inputs, and a post-build DLL copy step.
- Upgrading to `vcpkg` makes dependency management reproducible and easier to maintain.
- SDL3 is the lowest-risk migration because current runtime usage is already SDL-oriented and isolated to one concrete window class.

## Goals

- Remove direct dependency on vendored SDL2 SDK files from the `app` project.
- Use `vcpkg` manifest mode for windowing dependencies.
- Preserve current runtime behavior:
  - open a window
  - stream rendered pixels from the render thread
  - show render time text overlay
  - close on window close or `Esc`
- Keep the ray tracer core and unit tests independent from the windowing backend.

## Non-Goals

- Rewriting the ray tracer rendering pipeline.
- Changing scene generation or image output behavior.
- Migrating the whole repo to CMake in this change.
- Adding new UI features beyond parity with the current SDL2 app.

## Current State

- Backend interface exists in `src/appWindow.hpp`.
- Concrete implementation is `src/appWindowSDL.hpp` and `src/appWIndowSDL.cpp`.
- Backend selection is hardcoded in `src/main.cpp`.
- SDL2 linkage and DLL copying are defined in `project/windows/app.vcxproj` and `project/windows/copy_sdl2_dll.bat`.

## Decision

Primary implementation path:

- Adopt `vcpkg` manifest mode.
- Migrate the app backend from SDL2 to SDL3.
- Keep the existing `app::Window` abstraction and current threaded render model.

Alternatives considered:

- `SFML`: acceptable, but requires a larger API rewrite around `sf::RenderWindow`, textures, sprites, and text classes.
- `raylib`: acceptable for a future simplification pass, but less aligned with the current architecture and more opinionated about the frame loop.

## Phased Plan

### Phase 1: Dependency management

- Add `vcpkg.json` at repo root.
- Enable `VcpkgEnableManifest` for the Visual Studio app project or solution-wide MSBuild integration.
- Add `sdl3` and `sdl3-ttf` as dependencies.
- Remove manual SDL include/library paths from `app.vcxproj`.
- Remove `copy_sdl2_dll.bat` usage once vcpkg app-local deployment is working.

### Phase 2: Backend seam cleanup

- Add a small backend creation point so `main.cpp` no longer directly constructs `WindowSDL`.
- Keep `app::Window` as the stable interface.
- Ensure font asset lookup remains valid from the app output directory.

### Phase 3: SDL3 migration

- Update includes to SDL3 header paths.
- Remove `SDL2main.lib` assumptions and handle SDL3 startup correctly.
- Update API calls and error handling for SDL3 semantics.
- Keep pixel upload and text overlay behavior functionally equivalent.

### Phase 4: Validation

- Build `app`, `raytracer`, and `tests` in `Debug|x64`.
- Run unit tests.
- Manually verify:
  - window opens
  - pixels appear during rendering
  - render time text displays
  - `Esc` closes the app

## Acceptance Criteria

- No SDL2 vendored include or library paths remain in the active app project configuration.
- No post-build batch script is required for SDL DLL deployment.
- The app builds from a clean checkout after restoring `vcpkg` dependencies.
- Runtime behavior matches current SDL2 functionality.
- Core library and tests remain window-backend agnostic.

## Follow-Up

After SDL3 is stable, reassess whether a second-step migration to SFML or raylib still provides enough value to justify further churn.
