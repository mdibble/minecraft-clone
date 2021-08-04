#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 tex;
layout (location = 2) in vec3 normal;

out vec2 texCoord;
out vec3 normalVal;
out vec3 fragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main() {
    texCoord = tex;
    fragPos = vec3(model * vec4(pos, 1.0));
    normalVal = normal;

    gl_Position = proj * view * model * vec4(pos, 1.0);
}
