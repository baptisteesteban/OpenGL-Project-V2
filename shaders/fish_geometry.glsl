#version 450

layout(points) in;
layout(triangle_strip, max_vertices = 20) out;

void draw_fish(float offset)
{
  gl_Position = gl_in[0].gl_Position;
  for (float i = -0.01; i <= 0.01; i += 0.005) {
    float y = sqrt(pow(0.01, 2) - pow(i, 2));
    gl_Position = gl_in[0].gl_Position;
    gl_Position.x = gl_Position.x + i;
    gl_Position.y = gl_Position.y + y;
    EmitVertex();
    gl_Position = gl_in[0].gl_Position;
    gl_Position.x = gl_Position.x + i;
    gl_Position.y = gl_Position.y - y;
    EmitVertex();
  }
}

void main()
{
  draw_fish(0);
  EndPrimitive();
}
