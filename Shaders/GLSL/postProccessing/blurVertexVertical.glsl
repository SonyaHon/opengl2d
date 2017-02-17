#version 330 core
layout(location = 0) in vec2 coords;
layout(location = 1) in vec2 uv_coords;
out vec2 uvs[11];

uniform float TargetHeight;

void main() {

    gl_Position = vec4(coords.x, coords.y, 0.0, 1.0);

    vec2 centerTextureCoords = coords * 0.5 + 0.5;
    float pixelSize = 1.0 / TargetHeight;

    for(int i = -5; i <= 5; i++) {
        uvs[i+5] = centerTextureCoords + vec2(0.0, pixelSize * i);
    }

}
