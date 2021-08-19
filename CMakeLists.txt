cmake_minimum_required (VERSION 3.8)

project ("lightning")

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_executable (lightning "src/lightning.cpp" "src/lightning.h" "src/main.cpp" "src/render/shader.h" "src/render/shader.cpp" "src/render/renderer.h" "src/render/renderer.cpp" "src/render/vertex_buffer.cpp" "src/render/camera.h" "src/render/camera.cpp" "src/input/input.h" "src/input/input.cpp" "src/render/texture.h" "src/render/texture.cpp" "src/game/game.h" "src/game/chunk.h" "src/game/chunk.cpp" "src/game/world.h" "src/game/game.cpp" "src/game/world.cpp" "src/game/world_gen.h" "src/game/world_gen.cpp" "src/game/player.h" "src/game/player.cpp")

include_directories (PUBLIC vendor/glfw/include)
include_directories (PUBLIC vendor/glad/include)
include_directories (PUBLIC vendor/stb_image/)
include_directories (PUBLIC vendor/glm/)
include_directories (PUBLIC vendor/noise/)

add_library (stb_image vendor/stb_image/stb_image.cpp)
add_library (glad vendor/glad/src/glad.c)
add_library (noise vendor/noise/noise/noise.cpp)
add_subdirectory (vendor/glfw)
add_subdirectory (vendor/glm/glm)

target_link_libraries (lightning glfw glm glad noise stb_image)
