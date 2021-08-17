﻿#include "lightning.h"

Lightning::Lightning() {
    dt = 0.0f;
    lastFrameTime = glfwGetTime();
}

void Lightning::Init() {
    std::cout << "Initializing application" << std::endl;
    renderer.Init(&inputHandler, &dt, &lastFrameTime);
    game.Init();

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

        bool chunkLoadedThisFrame = false;

        for (int i = 0; i < 16; i += 1) {
            for (int j = 0; j < 16; j += 1) {
                if (!chunkLoadedThisFrame && game.world.GetChunk(i, j)->IsLoaded() == false) {
                    game.world.GetChunk(i, j)->LoadChunk();
                    chunkLoadedThisFrame = true;
                }
                renderer.DrawChunk(game.world.GetChunk(i, j));
            }
        }

        renderer.EndFrame();
    }
}
