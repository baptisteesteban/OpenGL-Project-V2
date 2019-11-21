#ifndef TRIANGLE_HH
# define TRIANGLE_HH

# include <program.hh>
# include <object.hh>

# include <GL/glew.h>
# include <initializer_list>
# include <vector>

class Triangle : public Object
{
public:
  Triangle() = delete;
  Triangle(const std::initializer_list<GLfloat>& points);

  void draw(const Camera& cam, const mat4f& proj);
  void update(const SDL_Event& e);

private:
  std::vector<GLfloat> points_;
  Program program_;
  GLuint vao_;
};

#endif /* !TRIANGLE_HH */