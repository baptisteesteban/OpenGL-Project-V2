#version 450

layout(points) in;
layout(triangle_strip, max_vertices = 20) out;

void draw_fish(float offset)
{
  gl_Position = gl_in[0].gl_Position;
  EmitVertex();
  gl_Position   = gl_in[0].gl_Position + offset;
  gl_Position.y = gl_Position.y - 0.1;
  EmitVertex();
  gl_Position   = gl_in[0].gl_Position + offset;
  gl_Position.y = gl_Position.y + 0.1;
  EmitVertex();
  gl_Position   = gl_in[0].gl_Position + offset;
  gl_Position.x = gl_Position.x + 0.15;
  EmitVertex();
  gl_Position   = gl_in[0].gl_Position + offset;
  gl_Position.y = gl_Position.y + 0.1;
  EmitVertex();
  gl_Position   = gl_in[0].gl_Position + offset;
  gl_Position.y = gl_Position.y - 0.1;
  EmitVertex();
  gl_Position   = gl_in[0].gl_Position + offset;
  gl_Position.x = gl_Position.x - 0.15;
  EmitVertex();

  gl_Position = gl_in[0].gl_Position + offset;
  EmitVertex();
  gl_Position   = gl_in[0].gl_Position + offset;
  gl_Position.x = gl_Position.x + 0.1;
  EmitVertex();
  gl_Position   = gl_in[0].gl_Position + offset;
  gl_Position.x = gl_Position.x + 0.1;
  EmitVertex();

  gl_Position   = gl_in[0].gl_Position + offset;
  gl_Position.x = gl_Position.x + 0.2;
  gl_Position.y = gl_Position.y + 0.1;
  EmitVertex();
  gl_Position   = gl_in[0].gl_Position + offset;
  gl_Position.x = gl_Position.x + 0.2;
  gl_Position.y = gl_Position.y - 0.1;
  EmitVertex();
}

void main()
{
  draw_fish(0);
  EndPrimitive();
}
