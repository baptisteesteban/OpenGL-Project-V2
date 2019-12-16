#ifndef FISH_HH
#define FISH_HH

#include <array>
#include <vector>

#include <GL/glew.h>

#include <compute_shader.hh>
#include <mat4f.hh>
#include <object.hh>
#include <program.hh>

namespace details
{
  struct fish_elem
  {
    float p[4];
    float f[4];
    float v[4];
  };
} // namespace details

class Fish : public Object
{
public:
  Fish(const std::vector<details::fish_elem>& points);

  void draw(const Camera& cam, const mat4f& proj);
  void update(const SDL_Event& e);

private:
  std::vector<details::fish_elem> elem_;
  Program                         program_;
  ComputeShader                   cs_;
  GLuint                          buffer_;
  GLuint                          vao_;
};

#endif /* !FISH_HH */
