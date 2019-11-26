#version 450

layout(local_size_x = 1024) in;

layout(std430, binding = 0) buffer position_buffer
{
  vec3 pos[];
};

void update(int i)
{
  pos[i].y += 0.1;
  if (pos[i].y >= 1)
    pos[i].y = 0;
}

void main()
{
  update(int(gl_GlobalInvocationID.x));
}
