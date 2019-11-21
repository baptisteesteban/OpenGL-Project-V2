#include <fstream>
#include <sstream>
#include <stdexcept>

#include <mat4f.hh>
#include <program.hh>

Program::Program(const std::string& vertex_shd_filename,
		         const std::string& fragment_shd_filename,
		         const std::string& geometry_shd_filename)
{
    bool use_geometry = geometry_shd_filename.size() > 0;

    /* Vertex shader */      
    std::ifstream if_vertex(vertex_shd_filename);
    if (!if_vertex.is_open())
	    throw std::invalid_argument("Vertex shader file could not be opened");

    std::stringstream ss_vertex;
    ss_vertex << if_vertex.rdbuf();
    std::string vertex_src_str = ss_vertex.str();
    const GLchar *vertex_src = (const GLchar*)vertex_src_str.c_str();
    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_src, NULL);
    GLint isCompiled = 0;
    glCompileShader(vertex_shader);
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE)
    {
	    GLint maxLength = 0;
	    glGetShaderiv(vertex_shader, GL_INFO_LOG_LENGTH, &maxLength);

	    GLchar log[maxLength];
	    glGetShaderInfoLog(vertex_shader, maxLength, &maxLength, &log[0]);

	    glDeleteShader(vertex_shader);
	
	    throw std::invalid_argument(vertex_shd_filename + ": " + log);
    }

    /* Fragment shader */
    std::ifstream if_fragment(fragment_shd_filename);
    if (!if_vertex.is_open())
	    throw std::invalid_argument("Fragment shader file could not be opened");

    std::stringstream ss_fragment;
    ss_fragment << if_fragment.rdbuf();
    std::string fragment_src_str = ss_fragment.str();
    const GLchar *fragment_src = (const GLchar*)fragment_src_str.c_str();
    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_src, NULL);
    glCompileShader(fragment_shader);
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE)
    {
	    GLint maxLength = 0;
	    glGetShaderiv(fragment_shader, GL_INFO_LOG_LENGTH, &maxLength);

	    GLchar log[maxLength];
	    glGetShaderInfoLog(fragment_shader, maxLength, &maxLength, &log[0]);

	    glDeleteShader(vertex_shader);
	    glDeleteShader(fragment_shader);
	
	    throw std::invalid_argument(vertex_shd_filename + ": " + log);
    }

    /* Geometry shader */
    GLuint geometry_shader;
    if (use_geometry)
    {
	    std::ifstream if_geometry(geometry_shd_filename);
	    if (!if_geometry.is_open())
	        throw std::invalid_argument("Geometry shader file could not be opened");
	
	    std::stringstream ss_geometry;
	    ss_geometry << if_geometry.rdbuf();
	    std::string geometry_src_str = ss_geometry.str();
	    const GLchar *geometry_src = (const GLchar*)geometry_src_str.c_str();
	    geometry_shader = glCreateShader(GL_GEOMETRY_SHADER);
	    glShaderSource(geometry_shader, 1, &geometry_src, NULL);
	    glCompileShader(geometry_shader);
	    glGetShaderiv(geometry_shader, GL_COMPILE_STATUS, &isCompiled);
	    if (isCompiled == GL_FALSE)
	    {
	        GLint maxLength = 0;
	        glGetShaderiv(geometry_shader, GL_INFO_LOG_LENGTH, &maxLength);
	    
	        GLchar log[maxLength];
	        glGetShaderInfoLog(geometry_shader, maxLength, &maxLength, &log[0]);
	    
	        glDeleteShader(vertex_shader);
	        glDeleteShader(fragment_shader);
	        glDeleteShader(geometry_shader);
	    
	        throw std::invalid_argument(geometry_shd_filename + ": " + log);
	    }
    }

    program_ = glCreateProgram();
    glAttachShader(program_, vertex_shader);
    glAttachShader(program_, fragment_shader);
    if (use_geometry)
	    glAttachShader(program_, geometry_shader);
    
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
	    glDeleteShader(vertex_shader);
	    glDeleteShader(fragment_shader);
	    if (use_geometry)
	        glDeleteShader(geometry_shader);
	
	    throw std::runtime_error("Could not link the program shader : " + std::string(log));
    }

    glDetachShader(program_, vertex_shader);
    glDetachShader(program_, fragment_shader);
    if (use_geometry)
	    glDetachShader(program_, geometry_shader);
    
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    if (use_geometry)
	    glDeleteShader(geometry_shader);
}

Program::~Program()
{
    glDeleteProgram(program_);
}

void
Program::use() const noexcept
{
    glUseProgram(program_);
}

void
Program::setUniformMatrix(const std::string& name, const mat4f& value)
{
    auto loc = glGetUniformLocation(program_, name.c_str());
    glUniformMatrix4fv(loc, 1, GL_FALSE, value.get_pointer_data());
}