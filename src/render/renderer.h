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
    void Init(InputHandler* inputHandlerPointer, float* dtPointer, float* lastFrameTime);
    void EndFrame();
    void BeginFrame();
    bool IsActive();
    void DrawMesh(float x, float y, float z);
    void PrepareMesh();
    void DrawSky();
    VertexArrayCollection vertexArrays;
private:
    GLFWwindow* window;
    Camera camera;
    InputHandler* inputHandler;
    int viewportW, viewportH;
    float* dt;
    float* lastFrameTime;
    void ViewportResizeCallback(int w, int h);
    void KeyCallback(int key, int scancode, int action, int mods);
    void MouseCallback(double xpos, double ypos);
};
