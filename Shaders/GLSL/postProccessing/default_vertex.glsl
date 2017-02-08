#version 330 core
layout(location = 0) in vec2 coords;
layout(location = 1) in vec2 uv_coords;
out vec2 uvs;
void main() {

    gl_Position = vec4(coords.x, coords.y, 0.0, 1.0);
    uvs = uv_coords;
}
