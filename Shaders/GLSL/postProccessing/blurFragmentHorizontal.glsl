#version 330 core

in vec2 uvs[11];

out vec4 fColor;

uniform sampler2D textureSampler;

void main() {
    fColor = vec4(0.0);
    fColor += texture(textureSampler, uvs[0]) * 0.0093;
    fColor += texture(textureSampler, uvs[1]) * 0.028002;
    fColor += texture(textureSampler, uvs[2]) * 0.065984;
    fColor += texture(textureSampler, uvs[3]) * 0.121703;
    fColor += texture(textureSampler, uvs[4]) * 0.175713;
    fColor += texture(textureSampler, uvs[5]) * 0.198596;
    fColor += texture(textureSampler, uvs[6]) * 0.175713;
    fColor += texture(textureSampler, uvs[7]) * 0.121703;
    fColor += texture(textureSampler, uvs[8]) * 0.065984;
    fColor += texture(textureSampler, uvs[9]) * 0.028002;
    fColor += texture(textureSampler, uvs[10]) * 0.0093;
}
