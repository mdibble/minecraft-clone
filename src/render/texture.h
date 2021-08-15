#pragma once

#include <string>
#include <iostream>
#include <glad/glad.h>
#include <stb_image.h>

class Texture {
public:
    Texture();
    void Init(std::string textPath);
    void Bind();
    void Unbind();
private:
    unsigned int id;
    unsigned char* localBuffer;
    int width, height, bpp;
};
