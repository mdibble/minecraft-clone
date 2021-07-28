#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shader.h"

class Renderer {
public:
    Renderer();
    void Init();
    void EndFrame();
    void BeginFrame();
private:
    ShaderCollection shaders;
    GLFWwindow* window;
    int viewportW, viewportH;
    void ViewportResizeCallback(int w, int h);
    void KeyCallback(int key, int scancode, int action, int mods);
};
