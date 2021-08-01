#pragma once

#include <glad/glad.h>
#include <stb_image.h>
#include <iostream>

#include "shader.h"

class VertexArray {
public:
    VertexArray();
    void Init(std::string vertPath, std::string fragPath);
    void Bind();
    void Unbind();
    void SendVerticies(float data[], int size);
    void SendIndicies(unsigned int data[], int size);
    void Draw();
private:
    Shader shader;
    unsigned int vao, vbo, ibo, texture;
    int elementCount;
};

class VertexArrayCollection {
public:
    void Init();
    void Unbind();
    VertexArray basic;
    VertexArray sky;
};
