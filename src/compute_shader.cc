#include <compute_shader.hh>

#include <fstream>
#include <sstream>
#include <stdexcept>

ComputeShader::ComputeShader(const std::string& filename)
{
  std::ifstream if_compute(filename);
  if (!if_compute.is_open())
    throw std::invalid_argument("Compute shader file could not be opened");

  std::stringstream ss_compute;
  ss_compute << if_compute.rdbuf();
  std::string   compute_src_str = ss_compute.str();
  const GLchar* compute_src     = (const GLchar*)compute_src_str.c_str();
  GLuint        compute_shader  = glCreateShader(GL_COMPUTE_SHADER);
  glShaderSource(compute_shader, 1, &compute_src, NULL);
  GLint isCompiled = 0;
  glCompileShader(compute_shader);
  glGetShaderiv(compute_shader, GL_COMPILE_STATUS, &isCompiled);
  if (isCompiled == GL_FALSE)
  {
    GLint maxLength = 0;
    glGetShaderiv(compute_shader, GL_INFO_LOG_LENGTH, &maxLength);

    GLchar log[maxLength];
    glGetShaderInfoLog(compute_shader, maxLength, &maxLength, &log[0]);

    glDeleteShader(compute_shader);

    throw std::invalid_argument(filename + ": " + log);
  }

  program_ = glCreateProgram();
  glAttachShader(program_, compute_shader);

  glLinkProgram(program_);
  GLint isLinked;
  glGetProgramiv(program_, GL_LINK_STATUS, &isLinked);
  if (isLinked == GL_FALSE)
  {
    GLint maxLength = 0;
    glGetProgramiv(program_, GL_INFO_LOG_LENGTH, &maxLength);

    GLchar log[maxLength];
    glGetProgramInfoLog(program_, maxLength, &maxLength, &log[0]);

    glDeleteProgram(program_);
    glDeleteShader(compute_shader);

    throw std::runtime_error("Could not link the program shader : " +
                             std::string(log));
  }

  glDetachShader(program_, compute_shader);

  glDeleteShader(compute_shader);
}

void ComputeShader::use(const GLuint x, const GLuint y, const GLuint z)
{
  glUseProgram(program_);
  glDispatchCompute(x, y, z);
  glMemoryBarrier(GL_ALL_BARRIER_BITS);
}

void ComputeShader::setUniformUnsigned(const std::string& name,
                                       const unsigned int value)
{
  auto loc = glGetUniformLocation(program_, name.c_str());
  glUniform1ui(loc, value);
}
