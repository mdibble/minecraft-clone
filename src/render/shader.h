#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include <glad/glad.h>

#include <glm/glm.hpp>

class Shader {
public:
    Shader();
    void Init(std::string vertPath, std::string fragPath);
    void Bind();
    void Unbind();
    void SetInt(const char* name, int val);
    void SetMat4(const char* name, glm::f32* ptr);
    void SetVec3(const char* name, glm::f32* ptr);
private:
    unsigned int id;
    bool DidCompilationSucceed(unsigned int shader);
    bool DidLinkingSucceed(unsigned int shader);
};
