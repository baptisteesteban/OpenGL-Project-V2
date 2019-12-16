#version 450

layout(location = 0) in vec4 p;

uniform mat4 projection;
uniform mat4 model_view;

void main()
{
  gl_Position = projection * model_view * p;
}
