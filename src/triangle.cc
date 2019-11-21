#include <triangle.hh>
#include <look_at.hh>

Triangle::Triangle(const std::initializer_list<GLfloat>& points)
  : points_(points)
  , program_("shaders/triangle_vertex.glsl", "shaders/triangle_fragment.glsl", "")
{
  glGenVertexArrays(1, &vao_);
  glBindVertexArray(vao_);

  GLuint vbo;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, points_.size() * sizeof(GLfloat), points_.data(), GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
  glEnableVertexAttribArray(0);

  glBindVertexArray(0);
}

void
Triangle::draw(const Camera& cam, const mat4f& proj)
{

  program_.use();
  program_.setUniformMatrix("model_view", transpose(lookAt(cam)));
  program_.setUniformMatrix("projection", transpose(proj));
  glBindVertexArray(vao_);
  glDrawArrays(GL_TRIANGLES, 0, 3);
  glBindVertexArray(0);
}

void
Triangle::update(const SDL_Event& e)
{(void)e;}