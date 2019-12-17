#include <camera_dialog.hh>

#include <iostream>

CameraDialog::CameraDialog(SDL_GLContext context, SDL_Window* window)
  : window_(window)
{
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGui_ImplSDL2_InitForOpenGL(window, context);
  ImGui_ImplOpenGL3_Init("#version 130");
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplSDL2_NewFrame(window);
}

void CameraDialog::render(const Camera& camera)
{
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplSDL2_NewFrame(window_);
  ImGui::NewFrame();
  ImGui::Begin("Camera");
  ImGui::Text("Pos: (%f, %f, %f)", camera.pos_get().x, camera.pos_get().y,
              camera.pos_get().z);
  ImGui::End();
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

CameraDialog::~CameraDialog()
{
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplSDL2_Shutdown();
  ImGui::DestroyContext();
}
