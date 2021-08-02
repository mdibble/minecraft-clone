#pragma once

#include <glad/glad.h>
#include <stb_image.h>
#include <iostream>

#include "shader.h"

class VertexArray {
public:
    VertexArray();
    Shader shader;
    void Init(std::string vertPath, std::string fragPath, std::string texPath);
    void Bind();
    void Unbind();
    void SendVerticies(float* data, int size);
    void SendIndicies(unsigned int* data, int size);
    void Draw();
private:
    unsigned int vao, vbo, ibo, texture;
    int elementCount;
};

class VertexArrayCollection {
public:
    void Init();
    VertexArray basic;
    VertexArray sky;
};
