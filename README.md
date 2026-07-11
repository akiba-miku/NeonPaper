# NeonPaper

NeonPaper is planned as a Wayland-native dynamic wallpaper engine for Arch Linux/Hyprland. It targets a focused Wallpaper Engine-like MVP for local video wallpapers without a GUI, workshop integration, web wallpapers, or a plugin system.

## Current status

This repository currently contains the initial architecture documentation and a minimal C++20/CMake project skeleton. Runtime wallpaper functionality is intentionally not implemented yet.

The only build targets are:

- `neonpaper`: future wallpaper daemon; currently supports `--help` and `--version`.
- `neonpaperctl`: future Unix Domain Socket control client; currently supports `--help` and `--version`.

## Planned MVP

The MVP will:

1. Connect to a Hyprland Wayland session.
2. Enumerate and select outputs.
3. Create non-interactive background layer surfaces through `wlr-layer-shell-unstable-v1`.
4. Loop local video wallpapers with audio muted by default.
5. Support `cover` and `contain` scaling.
6. Support `load`, `pause`, `resume`, `status`, and `quit` commands.
7. Handle output removal and compositor disconnects safely.
8. Avoid rendering or polling continuously when no new frame is available.

## Non-goals

NeonPaper will not implement the following for the MVP:

- Wallpaper Engine workshop compatibility.
- Web/Chromium wallpapers.
- Network URLs.
- GUI editing tools.
- Plugin or scripting systems.
- Playlists, transitions, or music visualization.
- Vulkan rendering.
- A custom FFmpeg decoder.
- A privileged system daemon.

## Build

```bash
cmake -S . -B build -G Ninja -DNEONPAPER_WARNINGS_AS_ERRORS=ON
cmake --build build
ctest --test-dir build --output-on-failure
```
