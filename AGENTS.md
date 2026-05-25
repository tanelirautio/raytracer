# AGENTS.md

This file applies to the entire repository.

## Project intent

- This repo implements *The Ray Tracer Challenge* closely and intentionally favors clarity over optimization.
- Keep changes aligned with the book's behavior unless the task explicitly asks for a deviation.
- Avoid speculative performance work or architectural rewrites.

## Repository layout

- `src/`: core ray tracer code (`rt*`) and app/window code (`app*`).
- `tests/MicrosoftUnitTestingFrameWork/`: native Visual Studio unit tests.
- `project/windows/`: Visual Studio 2022 solution and project files.
- `bin/`: built binaries and sample rendered images.
- `lib/`: vendored third-party dependencies. Do not modify unless the task specifically requires it.

## Build and test

- Primary target is Windows with Visual Studio 2022 and MSVC (`PlatformToolset=v143`).
- Build the solution from the repo root with:

```powershell
msbuild project\windows\raytracer.sln /t:Build /p:Configuration=Debug /p:Platform=x64
```

- The main application project writes outputs under `bin\`.
- Prefer validating changes with the existing unit tests in `tests/MicrosoftUnitTestingFrameWork/`.
- If using the IDE, use the `x64` configuration and run tests through Test Explorer.

## Code conventions

- Match the existing C++17 style and file pairing pattern: headers in `*.hpp`, implementations in `*.cpp`.
- Preserve the current naming scheme:
  - `rt*` for renderer/math/core types.
  - `app*` for windowing and example application code.
- Keep edits local and incremental. Extend existing types before introducing new abstractions.
- Follow the surrounding formatting in touched files rather than restyling unrelated code.

## Change guidance

- Add or update tests when changing renderer behavior, math primitives, intersections, materials, patterns, or world logic.
- Do not edit Visual Studio `.user` files unless the task explicitly depends on user-local settings.
- Treat sample output assets in `bin/` as generated artifacts unless the task is specifically about updating them.
