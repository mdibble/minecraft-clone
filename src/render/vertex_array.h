#pragma once

#include <glad/glad.h>
#include <iostream>

class VertexArray {
public:
    VertexArray();
    void Init();
    void Bind();
    void Unbind();
    void SendVerticies(float data[], int size);
    void SendIndicies(unsigned int data[], int size);
    void Draw();
private:
    unsigned int vao, vbo, ibo;
    int elementCount;
};

// Are multiple vertex buffers needed? Probably but I don't know for sure
class VertexArrayCollection {
public:
    void Init();
    void Unbind();
    VertexArray basic;
    VertexArray sky;
};
