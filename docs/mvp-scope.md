# MVP Scope

NeonPaper's MVP is deliberately small: it should prove that a local video can be rendered as a native Wayland background wallpaper on Hyprland with correct lifecycle management.

## Goals

- Connect to the active Wayland compositor.
- Discover available `wl_output` objects and choose a target output.
- Create a non-interactive background layer surface using `wlr-layer-shell-unstable-v1`.
- Render local videos through EGL/OpenGL and the libmpv Render API.
- Loop playback and mute audio by default.
- Support `cover` and `contain` placement modes.
- Expose `load`, `pause`, `resume`, `status`, and `quit` over `$XDG_RUNTIME_DIR/neonpaper.sock`.
- Stop rendering when no frame is pending.
- Survive output removal and compositor disconnects without use-after-free.

## Non-goals

- Wallpaper Engine workshop compatibility.
- Web or Chromium wallpapers.
- Network URL playback.
- GUI configuration or editing.
- Plugins, scripts, or embedded user code.
- Playlists, transitions, or music visualization.
- Vulkan support.
- Custom FFmpeg decode pipelines.
- System-level privileged daemon behavior.

## Milestones

### M0: Architecture and build skeleton

- Document architecture and lifecycle rules.
- Provide warning-clean C++20 executable stubs.
- Validate CMake, Ninja, and CTest.

### M1: Wayland solid-color background

- Connect to the compositor.
- Bind `wl_compositor`, `wl_output`, and layer-shell globals.
- Create a background layer surface for a selected output.
- Handle configure and output removal correctly.
- Provide a wakeable stop mechanism.
- Keep all Wayland proxy ownership explicit.

M1 must not introduce libmpv.

### M2: Video rendering

- Add EGL/OpenGL rendering.
- Integrate libmpv Render API.
- Wake the main loop from mpv callbacks via `eventfd` only.
