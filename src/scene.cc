#include <GL/glew.h>

#include <config.hh>
#include <frustum.hh>
#include <scene.hh>
#include <vec3f.hh>

#include <iostream>

Scene::Scene(const Camera& cam)
  : objs_(std::vector<std::shared_ptr<Object>>())
  , cam_(cam)
  , projection_(frustum(-1.f, 1.f, -1.f, 1.f, 0.1f, 10.f))
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
  if (e.type == SDL_KEYDOWN)
  {
    switch (e.key.keysym.sym)
    {
    case SDLK_LEFT:
      cam_.pos_set(cam_.pos_get() + vec3f{-0.1f, 0.f, 0.f});
      break;

    case SDLK_RIGHT:
      cam_.pos_set(cam_.pos_get() + vec3f{0.1f, 0.f, 0.f});
      break;

    case SDLK_UP:
      cam_.pos_set(cam_.pos_get() + vec3f{0.f, 0.1f, 0.f});
      break;

    case SDLK_DOWN:
      cam_.pos_set(cam_.pos_get() + vec3f{0.f, -0.1f, 0.f});
      break;

    case SDLK_z:
      cam_.pos_set(cam_.pos_get() + vec3f{0.f, 0.f, -0.01f});
      break;

    case SDLK_s:
      cam_.pos_set(cam_.pos_get() + vec3f{0.f, 0.f, 0.01f});
      break;

    default:
      break;
    }
  }
}
