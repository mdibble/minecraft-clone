#pragma once

#include <glad/glad.h>
#include <stb_image.h>
#include <iostream>
#include <vector>

#include "shader.h"

class VertexBuffer {
public:
    VertexBuffer();
    void Init();
    void Bind();
    void Unbind();
    void SendVerticies(float* data, int size);
    void SendIndicies(unsigned int* data, int size);
    void Draw();
private:
    unsigned int vao, vbo, ibo;
    int elementCount;
};
