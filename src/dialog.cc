#include <dialog.hh>

#include <iostream>

Dialog::Dialog(SDL_GLContext context, SDL_Window* window)
  : window_(window)
{
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGui_ImplSDL2_InitForOpenGL(window, context);
  ImGui_ImplOpenGL3_Init("#version 130");
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplSDL2_NewFrame(window);
}

void Dialog::render(const Camera& camera)
{
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplSDL2_NewFrame(window_);
  ImGui::NewFrame();
  ImGui::Begin("Informations");
  ImGui::Text("Pos: (%f, %f, %f)", camera.pos_get().x, camera.pos_get().y,
              camera.pos_get().z);
  ImGui::Text("X axis: (%f, %f, %f)", camera.x_axis_get().x,
              camera.x_axis_get().y, camera.x_axis_get().z);
  ImGui::Text("Y axis: (%f, %f, %f)", camera.y_axis_get().x,
              camera.y_axis_get().y, camera.y_axis_get().z);
  ImGui::Text("Z axis: (%f, %f, %f)", camera.z_axis_get().x,
              camera.z_axis_get().y, camera.z_axis_get().z);
  ImGui::End();
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

Dialog::~Dialog()
{
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplSDL2_Shutdown();
  ImGui::DestroyContext();
}
