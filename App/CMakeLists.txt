cmake_minimum_required(VERSION 3.10)

project("DirectX_project" VERSION 1.0)

configure_file(DirectX_projectConfig.h.in DirectX_project.h)

add_subdirectory(Moteur)
add_subdirectory(Tools)

set_property(DIRECTORY ${PROJECT_BINARY_DIR} PROPERTY VS_STARTUP_PROJECT "Moteur") # Pour start dans le projet DirectX_project