# NeonPaper Agent Notes

- Keep the project focused on a small, Wayland-native video wallpaper MVP for Arch Linux/Hyprland.
- Do not introduce GUI, plugin, web wallpaper, workshop, network streaming, or playlist features unless explicitly requested.
- Prefer C++20, move-only RAII ownership, and explicit lifetime boundaries.
- Wayland and EGL access must remain on the main thread.
- libmpv callbacks must only wake the main event loop and must not touch Wayland/EGL state directly.
- Keep CMake builds warning-clean with the configured warning set.
