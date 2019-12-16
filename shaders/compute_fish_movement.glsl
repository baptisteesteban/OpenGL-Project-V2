#version 450

struct element
{
  vec4 p;
  vec4 f;
  vec4 v;
};

layout(local_size_x = 1024) in;

layout(std430, binding = 0) buffer position_buffer
{
  element elem[];
};

void update(int i)
{
  elem[i].p.y += 0.1;
  if (elem[i].p.y >= 1)
    elem[i].p.y = 0;
}

void main()
{
  update(int(gl_GlobalInvocationID.x));
}
