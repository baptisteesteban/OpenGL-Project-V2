#include <GL/glew.h>

#include <config.hh>
#include <frustum.hh>
#include <scene.hh>
#include <vec3f.hh>

#include <iostream>

Scene::Scene(const Camera& cam, SDL_GLContext context, SDL_Window* window)
  : objs_(std::vector<std::shared_ptr<Object>>())
  , cam_(cam)
  , projection_(frustum(-1.f, 1.f, -1.f, 1.f, 0.1f, 10.f))
  , dialog_(context, window)
  , prev_x_(0)
  , prev_y_(0)
  , has_prev_(false)
{
}

void Scene::addObject(std::shared_ptr<Object> obj) noexcept
{
  objs_.push_back(obj);
}

void Scene::draw()
{
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  for (auto obj : objs_)
    obj->draw(cam_, projection_);
  dialog_.render(cam_);
  glFlush();
}

void Scene::update(const SDL_Event& e)
{
  updateCamera(e);
  for (auto obj : objs_)
    obj->update(e);
}

void Scene::updateCamera(const SDL_Event& e)
{
  constexpr float speed = 0.1f;
  if (e.type == SDL_KEYDOWN)
  {
    switch (e.key.keysym.sym)
    {
    case SDLK_LEFT:
      cam_.pos_set(cam_.pos_get() - speed * cam_.x_axis_get());
      break;

    case SDLK_RIGHT:
      cam_.pos_set(cam_.pos_get() + speed * cam_.x_axis_get());
      break;

    case SDLK_UP:
      cam_.pos_set(cam_.pos_get() + speed * cam_.y_axis_get());
      break;

    case SDLK_DOWN:
      cam_.pos_set(cam_.pos_get() - speed * cam_.y_axis_get());
      break;

    case SDLK_z:
      cam_.pos_set(cam_.pos_get() - speed * cam_.z_axis_get());
      break;

    case SDLK_s:
      cam_.pos_set(cam_.pos_get() + speed * cam_.z_axis_get());
      break;

    default:
      break;
    }
  }

  if (e.type == SDL_MOUSEMOTION && e.button.button == SDL_BUTTON_LEFT)
  {
    const auto& x = e.motion.x;
    const auto& y = e.motion.y;

    if (!has_prev_)
    {
      prev_x_   = x;
      prev_y_   = y;
      has_prev_ = true;
    }
    else
    {
      const auto dx = x - prev_x_;
      const auto dy = y - prev_y_;
      prev_x_       = x;
      prev_y_       = y;
      // FIXME: ROTATION
    }
  }

  if (e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_LEFT)
    has_prev_ = false;

  if (e.type == SDL_MOUSEWHEEL)
  {
    if (e.wheel.y > 0)
      std::cout << "UPW\n";

    if (e.wheel.y < 0)
      std::cout << "DOWNW\n";
  }
}
