#pragma once

#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "vertex_buffer.h"
#include "texture.h"
#include "camera.h"

#include "../input/input.h"
#include "../game/chunk.h"
#include "../game/player.h"

class Renderer {
public:
    Renderer();
    void Init(InputHandler* inputHandlerPointer, Player* playerPointer, float* dtPointer, float* lastFrameTime);
    void EndFrame();
    void BeginFrame();
    bool IsActive();
    void DrawChunk(Chunk* chunk);
    void PrepareMesh();
    void DrawSky();
private:
    GLFWwindow* window;
    InputHandler* inputHandler;
    Player* player;
    Camera camera;
    Texture basicTexture, skyTexture;
    Shader basicShader, skyShader;
    VertexBuffer skyVertexArray;
    int viewportW, viewportH;
    float* dt;
    float* lastFrameTime;
    void ViewportResizeCallback(int w, int h);
    void KeyCallback(int key, int scancode, int action, int mods);
    void MouseCallback(double xpos, double ypos);
};
