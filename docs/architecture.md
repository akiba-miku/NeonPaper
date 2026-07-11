# NeonPaper Architecture

NeonPaper is a Wayland-native dynamic wallpaper daemon for Arch Linux/Hyprland. The MVP focuses on local video wallpapers and intentionally avoids GUI, web, network, plugin, and workshop features.

## Technology choices

- **Language/build:** C++20 with CMake.
- **Compositor integration:** Native Wayland, without creating XWayland windows.
- **Wallpaper surface:** `wlr-layer-shell-unstable-v1` background layer.
- **Rendering:** EGL/OpenGL for presentation and context management.
- **Video:** libmpv Render API for local file playback.
- **Control:** `neonpaperctl` talks to the daemon through a Unix Domain Socket at `$XDG_RUNTIME_DIR/neonpaper.sock`.
- **Event loop:** Linux `epoll` coordinates the Wayland display FD, libmpv `eventfd`, IPC socket, and stop signal.

## Components

```text
Application
WaylandDisplay
WallpaperSession
LayerSurface
EglRenderer
MpvPlayback
IpcServer
```

### Application

`Application` is the composition root. It owns all long-lived subsystems, constructs them in dependency order, runs the main event loop, and tears them down in reverse dependency order.

### WaylandDisplay

`WaylandDisplay` owns the Wayland display connection, registry, and bound globals such as `wl_compositor`, `wl_output`, and layer-shell. It is responsible for registry events and compositor disconnect handling.

### WallpaperSession

Each output is managed by one `WallpaperSession`. A session uniquely owns the output-bound Wayland surface, layer surface, EGL surface, renderer state, and playback binding for that output. Output hot-unplug moves the session into a stopping state before any proxies are destroyed.

### LayerSurface

`LayerSurface` wraps the `wlr-layer-shell-unstable-v1` surface and associated `wl_surface`. It handles configure/ack-configure ordering, non-interactive background-layer placement, and frame callbacks.

### EglRenderer

`EglRenderer` owns EGL display/context resources and the per-session EGL surface. It is only accessed from the main thread and renders only when frame pacing and video updates require it.

### MpvPlayback

`MpvPlayback` owns libmpv state and Render API integration. libmpv may decode internally on its own threads, but mpv callbacks may only write to an `eventfd` to wake the main loop. They must not call Wayland/EGL functions and must not touch destroyed objects.

### IpcServer

`IpcServer` listens on `$XDG_RUNTIME_DIR/neonpaper.sock` and handles `load`, `pause`, `resume`, `status`, and `quit` requests.

## Threading and lifetime rules

- The main thread owns Wayland, EGL, rendering, IPC acceptance, and lifecycle decisions.
- libmpv internal threads are limited to decoding and callback notification.
- Callbacks from libmpv must only signal an `eventfd`.
- Wayland and EGL objects are never touched from libmpv callbacks.
- Prefer unique ownership and move-only RAII wrappers.
- Avoid `shared_ptr` as a way to hide unclear lifetimes.
- Destruction first disables callbacks and wake sources, then releases resources in reverse dependency order.
- Output removal must be handled as a normal state transition, not as an exceptional path.

## Frame pacing

NeonPaper must use `wl_surface.frame` callbacks to pace rendering. It must not run an unconditional 60 Hz loop. Rendering occurs only when the compositor is ready for a frame and playback or surface state requires an update.
