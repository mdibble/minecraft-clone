#include "lightning.h"

Lightning::Lightning() {
}

void Lightning::Init() {
    std::cout << "Initializing application" << std::endl;
    renderer.Init();
    std::cout << "App initialization complete" << std::endl;
}

void Lightning::Run() {
    float verticies[] = {
         0.5f,   0.5f,	 0.0f,       0.0f,   0.0f,
         0.5f,  -0.5f,	 0.0f,       0.0f,   0.0f,
        -0.5f,  -0.5f,	 0.0f,       0.0f,   0.0f,
        -0.5f,   0.5f,	 0.0f,       0.0f,   0.0f,
    };

    unsigned int indicies[] = {
        0, 1, 3,
        1, 2, 3,
    };

    while (true) {
        renderer.BeginFrame();
        renderer.DrawMesh(verticies, sizeof(verticies), indicies, sizeof(indicies));
        renderer.EndFrame();
    }
}
