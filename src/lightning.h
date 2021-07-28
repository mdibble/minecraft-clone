#pragma once

#include "render/renderer.h"

class Lightning {
public:
    Lightning();
    void Run();
    void Init();
private:
    Renderer renderer;
};
