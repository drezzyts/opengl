#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 color;
out vec2 textureCoord;

uniform float size;

uniform mat4 transform;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
  gl_Position = projection * view * (model * transform) * vec4(aPos.x * size, aPos.y * size, aPos.z * size, 1.0);
  color = aColor;
  textureCoord = aTexCoord;
}