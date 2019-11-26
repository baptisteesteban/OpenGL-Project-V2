#ifndef FISH_HH
#define FISH_HH

#include <initializer_list>
#include <vector>

#include <GL/glew.h>

#include <compute_shader.hh>
#include <mat4f.hh>
#include <object.hh>
#include <program.hh>

class Fish : public Object
{
public:
  Fish(std::initializer_list<float> points);

  void draw(const Camera& cam, const mat4f& proj);
  void update(const SDL_Event& e);

private:
  std::vector<float> points_;
  Program            program_;
  ComputeShader      cs_;
  GLuint             buffer_;
  GLuint             vao_;
};

#endif /* !FISH_HH */