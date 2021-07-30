cmake_minimum_required (VERSION 3.8)

project ("lightning")

include_directories (PUBLIC vendor/glfw/include)
include_directories (PUBLIC vendor/glad/include)

add_library (glad vendor/glad/src/glad.c "src/render/vertex_array.cpp")
add_subdirectory (vendor/glfw)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_executable (lightning "src/lightning.cpp" "src/lightning.h" "src/main.cpp" "src/render/shader.h" "src/render/shader.cpp" "src/render/renderer.h" "src/render/renderer.cpp" "src/render/vertex_array.cpp")

target_link_libraries (lightning glad glfw)
