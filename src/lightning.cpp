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
         // Bottom
        -0.5f,  -0.5f,	-0.5f,       0.0f,   0.0f,       0.0f,  -1.0f,   0.0f,
        -0.5f,  -0.5f,	 0.5f,       0.0f,   0.0625f,    0.0f,  -1.0f,   0.0f,
         0.5f,  -0.5f,	 0.5f,       0.0625f,0.0625f,    0.0f,  -1.0f,   0.0f,
         0.5f,  -0.5f,	-0.5f,       0.0625f,   0.0f,    0.0f,  -1.0f,   0.0f,

         // Top
        -0.5f,   0.5f,	-0.5f,       0.0f,   0.0625f,    0.0f,   1.0f,   0.0f,
        -0.5f,   0.5f,	 0.5f,       0.0f,   0.125f,     0.0f,   1.0f,   0.0f,
         0.5f,   0.5f,	 0.5f,       0.0625f,0.125f,     0.0f,   1.0f,   0.0f,
         0.5f,   0.5f,	-0.5f,       0.0625f,0.0625f,    0.0f,   1.0f,   0.0f,

         // Left side
        -0.5f,  -0.5f,	-0.5f,       0.0f,   0.125f,    -1.0f,   0.0f,   0.0f,
        -0.5f,   0.5f,	-0.5f,       0.0f,   0.1875f,   -1.0f,   0.0f,   0.0f,
        -0.5f,   0.5f,	 0.5f,       0.0625f,0.1875f,   -1.0f,   0.0f,   0.0f,
        -0.5f,  -0.5f,	 0.5f,       0.0625f,0.125f,    -1.0f,   0.0f,   0.0f,

         // Right side
         0.5f,  -0.5f,	 0.5f,       0.0f,   0.125f,     1.0f,   0.0f,   0.0f,
         0.5f,   0.5f,	 0.5f,       0.0f,   0.1875f,    1.0f,   0.0f,   0.0f,
         0.5f,   0.5f,	-0.5f,       0.0625f,0.1875f,    1.0f,   0.0f,   0.0f,
         0.5f,  -0.5f,	-0.5f,       0.0625f,0.125f,     1.0f,   0.0f,   0.0f,

         // Back side
         0.5f,  -0.5f,	-0.5f,       0.0f,   0.125f,     0.0f,   0.0f,  -1.0f,
         0.5f,   0.5f,	-0.5f,       0.0f,   0.1875f,    0.0f,   0.0f,  -1.0f,
        -0.5f,   0.5f,	-0.5f,       0.0625f,0.1875f,    0.0f,   0.0f,  -1.0f,
        -0.5f,  -0.5f,	-0.5f,       0.0625f,0.125f,     0.0f,   0.0f,  -1.0f,

         // Front side
        -0.5f,  -0.5f,	 0.5f,       0.0f,   0.125f,     0.0f,   0.0f,   1.0f,
        -0.5f,   0.5f,	 0.5f,       0.0f,   0.1875f,    0.0f,   0.0f,   1.0f,
         0.5f,   0.5f,	 0.5f,       0.0625f,0.1875f,    0.0f,   0.0f,   1.0f,
         0.5f,  -0.5f,	 0.5f,       0.0625f,0.125f,     0.0f,   0.0f,   1.0f,
    };

    std::vector<unsigned int> indicies = {
        // Bottom
        0, 1, 2,
        0, 2, 3,

        // Top
        4, 5, 6,
        4, 6, 7,

        // Left
        8, 9, 10,
        8, 10, 11,

        // Right
        12, 13, 14,
        12, 14, 15,

        // Back
        16, 17, 18,
        16, 18, 19,

        // Front
        20, 21, 22,
        20, 22, 23,
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
