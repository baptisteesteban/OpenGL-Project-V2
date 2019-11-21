#ifndef MAT4F_HH
# define MAT4F_HH

# include <array>
# include <initializer_list>

class mat4f
{
public:
    mat4f();
    mat4f(std::initializer_list<float>);
    mat4f(const mat4f&);
    mat4f& operator=(const mat4f&);
    ~mat4f();

    const float& at(std::size_t l, std::size_t c) const;
    float& at(std::size_t l, std::size_t c);

    friend std::ostream& operator<<(std::ostream&, const mat4f&);

    friend mat4f operator+(const mat4f&, const mat4f&);
    friend mat4f operator-(const mat4f&, const mat4f&);
    friend mat4f operator*(float e, const mat4f&);
    friend mat4f operator*(const mat4f&, float e);
    friend mat4f dot(const mat4f&, const mat4f&);

private:
    std::array<float, 16> data_;
};

#endif /* !MAT4F_HH */