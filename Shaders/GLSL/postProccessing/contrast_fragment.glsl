#version 330 core
in vec2 uvs;
out vec4 fColor;
uniform sampler2D textureSampler;
uniform float contrast;
void main() {
    fColor = texture(textureSampler, uvs);
    fColor.rgb = (fColor.rgb - 0.5) * (1.0 + contrast) + 0.5;
}
