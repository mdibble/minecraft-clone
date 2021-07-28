#pragma once

#include "shader.h"
#include <iostream>

class Renderer {
public:
    Renderer();
    void Init();
private:
    ShaderCollection shaders;
};
