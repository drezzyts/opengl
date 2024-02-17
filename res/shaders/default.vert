#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
    
out vec3 color;

uniform float size;
uniform mat4 transform;

void main() {
  gl_Position = transform * vec4(aPos.x * size, aPos.y * size, aPos.z * size, 1.0);
  color = aColor;
}