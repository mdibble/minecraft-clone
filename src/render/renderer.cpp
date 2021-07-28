#include "renderer.h"

Renderer::Renderer() {

}

void Renderer::Init() {
    std::cout << "Initializing renderer" << std::endl;
    shaders.Init();
}
