#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 uv_pos;

out vec2 uv;

uniform mat4 transformationMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main() {
    vec4 worldPosition = transformationMatrix * vec4(position, 1.0);
    gl_Position = projectionMatrix * viewMatrix * worldPosition;
    uv = uv_pos;
}
