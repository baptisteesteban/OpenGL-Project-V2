#version 450

layout (location = 0) in vec3 points;

uniform mat4 model_view;
uniform mat4 projection;

void main() {
  gl_Position = projection * model_view * vec4(points, 1.0f);
}