#include "lightning.h"

Lightning::Lightning() {
    dt = 0.0f;
    lastFrameTime = glfwGetTime();
}

void Lightning::Init() {
    std::cout << "Initializing application" << std::endl;
    renderer.Init(&inputHandler, &dt);
    std::cout << "App initialization complete" << std::endl;
}

void Lightning::Run() {
    while (renderer.IsActive()) {
        float currentTime = glfwGetTime();
        dt = currentTime - lastFrameTime;
        lastFrameTime = currentTime;

        renderer.BeginFrame();
        renderer.DrawSky();
        renderer.DrawMesh();

        renderer.EndFrame();
    }
}
