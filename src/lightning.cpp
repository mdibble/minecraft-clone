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
    std::vector<float> verticies = {
         0.5f,   0.5f,	 0.5f,       1.0f,   1.0f,
         0.5f,  -0.5f,	 0.5f,       1.0f,   0.0f,
        -0.5f,  -0.5f,	 0.5f,       0.0f,   0.0f,
        -0.5f,   0.5f,	 0.5f,       0.0f,   1.0f,

         0.5f,   0.5f,	-0.5f,       1.0f,   0.0f,
         0.5f,  -0.5f,	-0.5f,       0.0f,   1.0f,
        -0.5f,  -0.5f,	-0.5f,       1.0f,   1.0f,
        -0.5f,   0.5f,	-0.5f,       0.0f,   0.0f,
    };

    std::vector<unsigned int> indicies = {
        0, 1, 3,
        1, 2, 3,
        4, 5, 7,
        5, 6, 7,
        0, 4, 5,
        0, 1, 5,
        4, 0, 3,
        4, 7, 3,
        3, 6, 7,
        2, 3, 6,
        1, 2, 6,
        5, 6, 1
    };

    while (renderer.IsActive()) {
        float currentTime = glfwGetTime();
        dt = currentTime - lastFrameTime;
        lastFrameTime = currentTime;

        renderer.BeginFrame();
        renderer.DrawSky();
        renderer.DrawMesh(&verticies[0], verticies.size() * sizeof(float), &indicies[0], indicies.size() * sizeof(unsigned int));
        renderer.EndFrame();
    }
}
