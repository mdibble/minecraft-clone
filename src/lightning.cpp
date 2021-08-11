#include "lightning.h"

Lightning::Lightning() {
    dt = 0.0f;
    lastFrameTime = glfwGetTime();
}

void Lightning::Init() {
    std::cout << "Initializing application" << std::endl;
    renderer.Init(&inputHandler, &dt, &lastFrameTime);
    std::cout << "App initialization complete" << std::endl;
}

void Lightning::Run() {
    while (renderer.IsActive()) {
        float currentTime = glfwGetTime();
        dt = currentTime - lastFrameTime;
        lastFrameTime = currentTime;

        renderer.BeginFrame();
        renderer.DrawSky();

        for (float i = -10.0f; i < 10.0f; i += 1.0f) {
            for (int j = -10.0f; j < 10.0f; j += 1.0f) {
                renderer.DrawMesh(i, 0.0f, j);
            }
        }

        renderer.EndFrame();
    }
}
