#version 330 core

in vec2 pos;

out vec4 fColor;

uniform vec2 centerPos;
uniform float radius;
uniform vec4 color;

bool check(vec2 pos) {
    if(((pos.x - centerPos.x)*(pos.x - centerPos.x) + (pos.y - centerPos.y)*(pos.y - centerPos.y)) <= radius*radius) {
        return true;
    }
    return false;
}

void main() {

    if(check(pos)) fColor = color;
    else fColor = vec4(0, 0, 0, 0);

}
