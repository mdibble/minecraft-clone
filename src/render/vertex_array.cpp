#include "vertex_array.h"

VertexArray::VertexArray() {
    vao = 0;
    vbo = 0;
    ibo = 0;
    elementCount = 0;
}

void VertexArray::Init() {
    std::cout << "Initializing vertex array" << std::endl;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ibo);
    Bind();

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

    Unbind();
}

void VertexArray::SendVerticies(float data[], int size) {
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

void VertexArray::SendIndicies(unsigned int data[], int size) {
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    
    // Not sure how reliable this is 
    elementCount = size / sizeof(unsigned int);
}

void VertexArray::Draw() {
    glDrawElements(GL_TRIANGLES, elementCount, GL_UNSIGNED_INT, 0);
}

void VertexArray::Bind() {
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
}

void VertexArray::Unbind() {
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void VertexArrayCollection::Unbind() {
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void VertexArrayCollection::Init() {
    std::cout << "Initializing vertex array collection" << std::endl;
    basic.Init();
    sky.Init();
}
