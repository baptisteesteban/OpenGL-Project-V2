#ifndef PROGRAM_HH
# define PROGRAM_HH

# include <GL/glew.h>

# include <string>

# include <mat4f.hh>

class Program
{
public:
    Program() = delete;
    Program(const std::string& vertex_shd_filename,
            const std::string& fragment_shd_filename,
            const std::string& geometry_shd_filename = "");
    ~Program();

    void use() const noexcept;

    void setUniformMatrix(const std::string&, const mat4f&);

private:
    GLuint program_;
};

#endif /* !PROGRAM_HH */