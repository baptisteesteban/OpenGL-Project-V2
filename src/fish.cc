#include <fish.hh>
#include <look_at.hh>

#include <iostream>

Fish::Fish(const std::vector<details::fish_elem>& elem)
  : elem_(elem)
  , program_("shaders/fish_vertex.glsl", "shaders/fish_fragment.glsl")
  , cs_("shaders/compute_fish_movement.glsl")
  , old_time_(0)
{
  glGenVertexArrays(1, &vao_);
  glGenBuffers(1, &buffer_);

  glBindVertexArray(vao_);
  glBindBuffer(GL_ARRAY_BUFFER, buffer_);
  glBufferData(GL_ARRAY_BUFFER, elem_.size() * sizeof(details::fish_elem),
               elem_.data(), GL_DYNAMIC_DRAW);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(details::fish_elem),
                        (void*)0);
  glEnableVertexAttribArray(0);
  glBindVertexArray(0);

  glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, buffer_);
}

void Fish::draw(const Camera& cam, const mat4f& proj)
{
  program_.use();
  program_.setUniformMatrix("model_view", transpose(lookAt(cam)));
  program_.setUniformMatrix("projection", transpose(proj));

  glBindVertexArray(vao_);
  glDrawArrays(GL_POINTS, 0, elem_.size());
  glBindVertexArray(0);
}

void Fish::update(const SDL_Event& e)
{
  auto new_time = SDL_GetTicks();
  auto fps      = new_time - old_time_;
  cs_.use(elem_.size(), 1, 1);
  cs_.setUniformUnsigned("fps", fps);
  old_time_ = new_time;
}
