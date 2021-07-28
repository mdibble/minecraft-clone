#pragma once

#include <iostream>

class Shader {
public:
    Shader();
    void Init(const char* vertPath, const char* fragPath);
    void Bind();
    void Unbind();
private:
    unsigned int id;
};

class ShaderCollection {
public:
    ShaderCollection();
    void Init();
private:
    Shader basic;
    Shader sky;
};
