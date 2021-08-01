#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include <glad/glad.h>

class Shader {
public:
    Shader();
    void Init(std::string vertPath, std::string fragPath);
    void Bind();
    void Unbind();
    void SetInt(const char* name, int val);
private:
    unsigned int id;
    bool DidCompilationSucceed(unsigned int shader);
    bool DidLinkingSucceed(unsigned int shader);
};
