﻿#include "lightning.h"

Lightning::Lightning() {
}

void Lightning::Init() {
    std::cout << "Initializing application" << std::endl;
    renderer.Init();
    std::cout << "App initialization complete" << std::endl;
}

void Lightning::Run() {
    std::vector<float> verticies = {
         0.5f,   0.5f,	 0.0f,       1.0f,   1.0f,
         0.5f,  -0.5f,	 0.0f,       1.0f,   0.0f,
        -0.5f,  -0.5f,	 0.0f,       0.0f,   0.0f,
        -0.5f,   0.5f,	 0.0f,       0.0f,   1.0f,
    };

    std::vector<unsigned int> indicies = {
        0, 1, 3,
        1, 2, 3,
    };

    while (true) {
        renderer.BeginFrame();
        renderer.DrawSky();
        renderer.DrawMesh(&verticies[0], verticies.size() * sizeof(float), &indicies[0], indicies.size() * sizeof(unsigned int));
        renderer.EndFrame();
    }
}
