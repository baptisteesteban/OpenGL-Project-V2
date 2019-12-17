#ifndef SCENE_HH
#define SCENE_HH

#include <camera.hh>
#include <object.hh>

#include <camera_dialog.hh>

#include <memory>
#include <vector>

class Scene
{
public:
  Scene(const Camera& cam, SDL_GLContext context, SDL_Window* window);
  void addObject(std::shared_ptr<Object> obj) noexcept;
  void draw();
  void update(const SDL_Event& e);

private:
  void                                 updateCamera(const SDL_Event& e);
  std::vector<std::shared_ptr<Object>> objs_;
  Camera                               cam_;
  mat4f                                projection_;
  CameraDialog                         dialog_;
};

#endif /* !SCENE_HH */
