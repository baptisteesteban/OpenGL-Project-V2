#include <fish.hh>
#include <look_at.hh>

#include <iostream>

Fish::Fish(std::initializer_list<float> points)
  : points_(points)
  , program_("shaders/fish_vertex.glsl", "shaders/fish_fragment.glsl")
  , cs_("shaders/compute_fish_movement.glsl")
{
  if (points.size() % 3 != 0)
    throw std::invalid_argument(
        "point argument should be an array of size 3 * n");
  glGenVertexArrays(1, &vao_);
  glGenBuffers(1, &buffer_);

  glBindVertexArray(vao_);
  glBindBuffer(GL_ARRAY_BUFFER, buffer_);
  glBufferData(GL_ARRAY_BUFFER, points_.size() * sizeof(float), points_.data(),
               GL_DYNAMIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat),
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
  glDrawArrays(GL_POINTS, 0, points_.size() / 3);
  glBindVertexArray(0);
}

void Fish::update(const SDL_Event& e)
{
  cs_.use(points_.size() / 3, 1, 1);
}
