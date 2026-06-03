# Phase 1: Dependency management

## Tasks
- [x] Add `vcpkg.json` at repo root.
- [x] Enable `VcpkgEnableManifest` for the Visual    Studio app project or solution-wide MSBuild integration.
- [x] Add `sdl3` and `sdl3-ttf` as dependencies.
- [x] Remove manual SDL include/library paths from `app.vcxproj`.
- [x] Remove `copy_sdl2_dll.bat` usage once vcpkg app-local deployment is working.
- [x] Clean up unused vendored SDL2 binaries in `lib/windows/`.
