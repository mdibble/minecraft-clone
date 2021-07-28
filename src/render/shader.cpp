#include "shader.h"

Shader::Shader() {
    id = 0;
}

void Shader::Init(const char* vertPath, const char* fragPath) {
    std::cout << "Initializing shader" << std::endl;
    if (id != 0) {
        std::cout << "Shader already created" << std::endl;
        return;
    }
}

void Shader::Bind() {

}

void Shader::Unbind() {

}

ShaderCollection::ShaderCollection() {

}

void ShaderCollection::Init() {
    std::cout << "Initializing shader collection" << std::endl;
    basic.Init("shader/basic.vert", "shader/basic.frag");
    sky.Init("shader/sky.vert", "shader/sky.frag");
}
