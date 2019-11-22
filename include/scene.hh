#ifndef SCENE_HH
#define SCENE_HH

#include <camera.hh>
#include <object.hh>

#include <memory>
#include <vector>

class Scene
{
public:
  Scene(const Camera& cam);
  void addObject(std::shared_ptr<Object> obj) noexcept;
  void draw();
  void update(const SDL_Event& e);

private:
  void                                 updateCamera(const SDL_Event& e);
  std::vector<std::shared_ptr<Object>> objs_;
  Camera                               cam_;
  mat4f                                projection_;
};

#endif /* !SCENE_HH */
