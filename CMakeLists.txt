cmake_minimum_required(VERSION 3.25)

project(NeonPaper
    VERSION 0.1.0
    DESCRIPTION "Wayland-native dynamic wallpaper engine for Hyprland"
    LANGUAGES CXX
)

option(NEONPAPER_WARNINGS_AS_ERRORS "Treat compiler warnings as errors" OFF)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(cmake/CompilerWarnings.cmake)
include(CTest)

add_executable(neonpaper src/neonpaper/main.cpp)
target_compile_definitions(neonpaper PRIVATE NEONPAPER_VERSION="${PROJECT_VERSION}")
neonpaper_enable_warnings(neonpaper)

add_executable(neonpaperctl src/neonpaperctl/main.cpp)
target_compile_definitions(neonpaperctl PRIVATE NEONPAPER_VERSION="${PROJECT_VERSION}")
neonpaper_enable_warnings(neonpaperctl)

if(BUILD_TESTING)
    add_test(NAME neonpaper_version COMMAND neonpaper --version)
    set_tests_properties(neonpaper_version PROPERTIES PASS_REGULAR_EXPRESSION "NeonPaper ${PROJECT_VERSION}")

    add_test(NAME neonpaperctl_version COMMAND neonpaperctl --version)
    set_tests_properties(neonpaperctl_version PROPERTIES PASS_REGULAR_EXPRESSION "neonpaperctl ${PROJECT_VERSION}")
endif()
