cmake_minimum_required(VERSION 3.28)

project(NeonPaper LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS
  Core
  Gui
  Quick
  QuickControls2
)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(neonpaper-desktop
  main.cpp
)

qt_add_qml_module(neonpaper-desktop
  URI NeonPaper
  VERSION 1.0
  QML_FILES
    main.qml
)

target_link_libraries(neonpaper-desktop
  PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Quick
    Qt6::QuickControls2
)
