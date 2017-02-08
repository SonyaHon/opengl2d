#version 330 core
in vec2 uvs;
out vec4 fColor;
uniform sampler2D textureSampler;
void main() {
    fColor = texture(textureSampler, uvs);
}
