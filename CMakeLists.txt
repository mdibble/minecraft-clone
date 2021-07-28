cmake_minimum_required (VERSION 3.8)

project ("lightning")

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_executable (lightning "src/lightning.cpp" "src/lightning.h" "src/main.cpp" "src/render/shader.h" "src/render/shader.cpp" "src/render/renderer.h" "src/render/renderer.cpp")
