#pragma once

#include "render/renderer.h"
#include "input/input.h"

class Lightning {
public:
    Lightning();
    void Run();
    void Init();
private:
    Renderer renderer;
    InputHandler inputHandler;
    Chunk chunkTest;
    float dt;
    float lastFrameTime;
};
