#version 330 core

out vec4 color;

in vec2 texCoord;
in vec3 normalVal;
in vec3 fragPos;

uniform sampler2D textureData;
uniform vec3 lightPos;

void main() {
    float ambient_str = 0.6;

    vec3 norm = normalize(normalVal);
    vec3 lightDir = normalize(lightPos - fragPos);
    float diff = max(dot(norm, lightDir), 0.0);

    color = (ambient_str + diff) * texture(textureData, texCoord);
}
