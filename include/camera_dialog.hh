#ifndef CAMERA_DIALOG_HH
#define CAMERA_DIALOG_HH

#include <camera.hh>

#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_sdl.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

class CameraDialog
{
public:
  CameraDialog(SDL_GLContext context, SDL_Window* window);
  void render(const Camera& camera);
  ~CameraDialog();

private:
  SDL_Window* window_;
};

#endif /* !CAMERA_DIALOG_HH */
