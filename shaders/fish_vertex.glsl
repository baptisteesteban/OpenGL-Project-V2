#version 450

layout(location = 0) in vec3 points;

uniform mat4 projection;
uniform mat4 model_view;

void main()
{
  gl_Position = projection * model_view * vec4(points, 1.0);
}