#include <iostream>

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <config.hh>
#include <scene.hh>
#include <triangle.hh>

#include <frustum.hh>
#include <look_at.hh>
#include <mat4f.hh>
#include <vec3f.hh>

bool init_glew()
{
  GLenum err = glewInit();
  if (err != GLEW_OK)
  {
    std::cerr << "Glew init: " << glewGetErrorString(err) << std::endl;
    return false;
  }
  return true;
}

void init_gl()
{
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_POINT_SIZE);
  glPointSize(100);
}

int main(int argc, char** argv)
{
  SDL_Window* window = SDL_CreateWindow(wtitle, 0, 0, wwidth, wheight,
                                        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
  if (!window)
  {
    std::cerr << "Window creation: error\n";
    return 1;
  }

  SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GLContext context = SDL_GL_CreateContext(window);

  if (!init_glew())
    return 1;
  init_gl();
  Camera cam(vec3f{0.f, 0.f, 1.0f}, vec3f{1.0f, 0.f, 0.f},
             vec3f{0.f, 1.f, 0.f});
  Scene  s(cam);

  auto points = {0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f};
  s.addObject(std::make_shared<Triangle>(points));

  auto proj       = frustum(-1, 1, -1, 1, 0.1, 10);
  auto model_view = lookAt(cam);

  bool running = true;
  while (running)
  {
    SDL_Event event;
    SDL_PollEvent(&event);

    if (event.type == SDL_QUIT)
      running = false;

    s.update(event);
    s.draw();

    SDL_GL_SwapWindow(window);
  }

  SDL_DestroyWindow(window);

  return 0;
}