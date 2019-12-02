#version 450

layout(points) in;
layout(points, max_vertices = 2) out;


void main()
{
  gl_Position = gl_in[0].gl_Position;
  EmitVertex();
  gl_Position   = gl_in[0].gl_Position;
  gl_Position.y = -1 * gl_in[0].gl_Position.y;
  EmitVertex();
  EndPrimitive();
}
