#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shader.h"
#include "vertex_array.h"

class Renderer {
public:
    Renderer();
    void Init();
    void EndFrame();
    void BeginFrame();
    void DrawMesh(float vert[], int vertCount, unsigned int ind[], int indCount);
private:
    ShaderCollection shaders;
    VertexArrayCollection vertexArrays;
    GLFWwindow* window;
    int viewportW, viewportH;
    void ViewportResizeCallback(int w, int h);
    void KeyCallback(int key, int scancode, int action, int mods);
};
