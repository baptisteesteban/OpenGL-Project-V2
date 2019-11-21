#ifndef OBJECT_HH
# define OBJECT_HH

# include <SDL2/SDL.h>

# include <camera.hh>
# include <mat4f.hh>

class Object
{
public:
  virtual void draw(const Camera& cam, const mat4f& proj) = 0;
  virtual void update(const SDL_Event& e) = 0;
};

#endif /* !OBJECT_HH */