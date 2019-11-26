#ifndef COMPUTE_SHADER_HH
#define COMPUTE_SHADER_HH

#include <GL/glew.h>

#include <string>

class ComputeShader
{
public:
  explicit ComputeShader(const std::string& filename);
  void use(const GLuint x, const GLuint y, const GLuint z);

  void setUniformUnsigned(const std::string& name, const unsigned int value);

private:
  GLuint program_;
};

#endif /* !COMPUTE_SHADER_HH */