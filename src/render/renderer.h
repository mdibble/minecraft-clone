#pragma once

#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "vertex_array.h"
#include "camera.h"

#include "../input/input.h"

class Renderer {
public:
    Renderer();
    void Init();
    void EndFrame();
    void BeginFrame();
    bool IsActive();
    void DrawMesh(float vert[], int vertCount, unsigned int ind[], int indCount);
    void DrawSky();
    void BindInputHandler(InputHandler* inputHandler);
private:
    VertexArrayCollection vertexArrays;
    GLFWwindow* window;
    Camera camera;
    InputHandler* inputHandler;
    int viewportW, viewportH;
    void ViewportResizeCallback(int w, int h);
    void KeyCallback(int key, int scancode, int action, int mods);
};
