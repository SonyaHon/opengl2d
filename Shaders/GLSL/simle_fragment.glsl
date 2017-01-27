#version 330 core

in vec2 uv;

out vec4 fColor;

uniform sampler2D textureSampler;

void main() {
    fColor = texture(textureSampler, uv);
}
