#include "lightning.h"

Lightning::Lightning() {
    dt = 0.0f;
    lastFrameTime = (float)glfwGetTime();
}

void Lightning::Init() {
    std::cout << "Initializing application" << std::endl;
    game.Init(&inputHandler);
    renderer.Init(&inputHandler, &(game.player), &dt, &lastFrameTime);

    std::cout << "App initialization complete" << std::endl;
}

void Lightning::Run() {
    while (renderer.IsActive()) {
        float currentTime = (float)glfwGetTime();
        dt = currentTime - lastFrameTime;
        lastFrameTime = currentTime;

        game.player.CheckCollision();

        game.player.UpdateMovementFromInputs(&dt);
        game.player.UpdatePosFromVel();
        game.player.UpdateVel(&dt);

        renderer.BeginFrame();
        renderer.DrawSky();
        renderer.PrepareMesh();

        bool chunkLoadedThisFrame = false;

        for (int i = 0; i < 16; i += 1) {
            for (int j = 0; j < 16; j += 1) {
                Chunk* chunk = game.world.GetChunk(i, j);
                
                if (!chunkLoadedThisFrame && chunk->IsLoaded() == false) {
                    chunk->LoadChunk();
                    chunkLoadedThisFrame = true;
                }
                if (chunk->NeedsUpdate()) {
                    chunk->UpdateMesh();
                }
                renderer.DrawChunk(game.world.GetChunk(i, j));
            }
        }

        game.player.Debug();
        renderer.EndFrame();
    }
}
