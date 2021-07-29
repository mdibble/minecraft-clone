#include "shader.h"

Shader::Shader() {
    id = 0;
}

void Shader::Init(std::string vertPath, std::string fragPath) {
    std::cout << "Initializing shader with paths: " << vertPath << ", " << fragPath << std::endl;
    if (id != 0) {
        std::cout << "Shader already created" << std::endl;
        return;
    }

    std::string vertSource;
    std::string fragSource;

    std::ifstream vertFile, fragFile;

    vertFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fragFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        vertFile.open(vertPath);
        fragFile.open(fragPath);
        std::stringstream vertStream, fragStream;

        vertStream << vertFile.rdbuf();
        fragStream << fragFile.rdbuf();

        vertFile.close();
        fragFile.close();

        vertSource = vertStream.str();
        fragSource = fragStream.str();
    }
    catch (std::ifstream::failure& e) {
        std::cout << "Error: Shader file could not be read" << std::endl;
    }

    const char* vertCStr = vertSource.c_str();
    const char* fragCStr = fragSource.c_str();

    unsigned int vert, frag;

    vert = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vert, 1, &vertCStr, NULL);
    glCompileShader(vert);
    if (!DidCompilationSucceed(vert)) {
        return;
    }

    frag = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(frag, 1, &fragCStr, NULL);
    glCompileShader(frag);
    if (!DidCompilationSucceed(frag)) {
        return;
    }

    id = glCreateProgram();
    glAttachShader(id, vert);
    glAttachShader(id, frag);
    glLinkProgram(id);
    if (!DidLinkingSucceed(id)) {
        return;
    }

    glDeleteShader(vert);
    glDeleteShader(frag);
}

void Shader::Bind() {
    glUseProgram(id);
}

void Shader::Unbind() {
    glUseProgram(0);
}

bool Shader::DidCompilationSucceed(unsigned int shader) {
    int success;
    char infoLog[1024];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 1024, NULL, infoLog);
        std::cout << "Shader compile error!" << std::endl << infoLog << std::endl;
        return false;
    }
    return true;
}

bool Shader::DidLinkingSucceed(unsigned int shader) {
    int success;
    char infoLog[1024];
    glGetProgramiv(shader, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shader, 1024, NULL, infoLog);
        std::cout << "Shader link error!" << std::endl << infoLog << std::endl;
        return false;
    }
    return true;
}

ShaderCollection::ShaderCollection() {
}

void ShaderCollection::Unbind() {
    glUseProgram(0);
}

void ShaderCollection::Init() {
    std::cout << "Initializing shader collection" << std::endl;
    basic.Init("shader/basic.vert", "shader/basic.frag");
    sky.Init("shader/sky.vert", "shader/sky.frag");
}
