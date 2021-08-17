#pragma once

#include "render/renderer.h"
#include "input/input.h"
#include "game/game.h"

class Lightning {
public:
    Lightning();
    void Run();
    void Init();
private:
    Renderer renderer;
    InputHandler inputHandler;
    Game game;
    float dt;
    float lastFrameTime;
};
