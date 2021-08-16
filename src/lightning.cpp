#include "lightning.h"

Lightning::Lightning() {
    dt = 0.0f;
    lastFrameTime = glfwGetTime();
}

void Lightning::Init() {
    std::cout << "Initializing application" << std::endl;
    renderer.Init(&inputHandler, &dt, &lastFrameTime);

    chunkTest.Init();

    std::cout << "App initialization complete" << std::endl;
}

void Lightning::Run() {
    while (renderer.IsActive()) {
        float currentTime = glfwGetTime();
        dt = currentTime - lastFrameTime;
        lastFrameTime = currentTime;

        renderer.BeginFrame();

        renderer.DrawSky();

        renderer.PrepareMesh();

        for (int i = 0; i < 16 * 16; i += 16) {
            for (int j = 0; j < 16 * 16; j += 16) {
                renderer.DrawChunk(&chunkTest, i, j);
            }
        }

        renderer.EndFrame();
    }
}
