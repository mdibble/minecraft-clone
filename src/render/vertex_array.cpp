#include "vertex_array.h"

VertexArray::VertexArray() {
    vao = 0;
    vbo = 0;
    ibo = 0;
    texture = 0;
    elementCount = 0;
}

void VertexArray::Init(std::string vertPath, std::string fragPath, std::string texPath) {
    std::cout << "Initializing vertex array [With texture]" << std::endl;
    
    shader.Init(vertPath, fragPath);

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ibo);
    Bind();

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    int texW, texH, texNrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(texPath.c_str(), &texW, &texH, &texNrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texW, texH, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    shader.SetInt("textureData", 0);

    Unbind();
}

void VertexArray::Init(std::string vertPath, std::string fragPath) {
    std::cout << "Initializing vertex array [No texture]" << std::endl;

    shader.Init(vertPath, fragPath);

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ibo);
    Bind();

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    Unbind();
}

void VertexArray::SendVerticies(float* data, int size) {
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

void VertexArray::SendIndicies(unsigned int* data, int size) {
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    
    // Not sure how reliable this is 
    elementCount = size / sizeof(unsigned int);
}

void VertexArray::Draw() {
    glDrawElements(GL_TRIANGLES, elementCount, GL_UNSIGNED_INT, 0);
}

void VertexArray::Bind() {
    shader.Bind();
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glBindTexture(GL_TEXTURE_2D, texture);
}

void VertexArray::Unbind() {
    shader.Unbind();
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void VertexArrayCollection::Init() {
    std::cout << "Initializing vertex array collection" << std::endl;
    basic.Init("shader/basic.vert", "shader/basic.frag", "texture/basic.jpg");
    sky.Init("shader/sky.vert", "shader/sky.frag", "texture/sky.jpg");
}
