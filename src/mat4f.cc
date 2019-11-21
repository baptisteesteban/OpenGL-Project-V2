#include <algorithm>
#include <ostream>

#include "mat4f.hh"

mat4f::mat4f()
{
    std::fill(data_.begin(), data_.end(), 0);
}

mat4f::mat4f(std::initializer_list<float> ini)
{
    if (ini.size() != 16)
        throw std::invalid_argument("The initializer list must have a size of 16");
    std::copy(ini.begin(), ini.end(), data_.begin());
}
    
mat4f::mat4f(const mat4f& M)
{
    std::copy(M.data_.begin(), M.data_.end(), data_.begin());
}

mat4f&
mat4f::operator=(const mat4f& M)
{
    std::copy(M.data_.begin(), M.data_.end(), data_.begin());
    return *this;
}

mat4f::~mat4f() {}

const float&
mat4f::at(std::size_t l, std::size_t c) const
{
    return data_[l * 4 + c];
}

float&
mat4f::at(std::size_t l, std::size_t c)
{
    return data_[l * 4 + c];
}


std::ostream& operator<<(std::ostream& out, const mat4f& M)
{
    for (std::size_t l = 0; l < 4; l++)
    {
        out << "|";
        for (std::size_t c = 0; c < 3; c++)
            out << M.data_[l * 4 + c] << " ";
        out << M.data_[l * 4 + 3] << "|\n";
    }
    return out;
}
mat4f operator+(const mat4f& A, const mat4f& B)
{
    mat4f res;
    for (std::size_t i = 0; i < 16; i++)
        res.data_[i] = A.data_[i] + B.data_[i];
    return res;
}

mat4f operator-(const mat4f& A, const mat4f& B)
{
    return A + (-1) * B;
}

mat4f operator*(float e, const mat4f& M)
{
    mat4f res;
    for (std::size_t i = 0; i < 16; i++)
        res.data_[i] = M.data_[i] * e;
    return res;
}

mat4f operator*(const mat4f& M, float e)
{
    return e * M;
}

mat4f dot(const mat4f& A, const mat4f& B)
{
    mat4f res;
    for (std::size_t l = 0; l < 4; l++)
    {
        for (std::size_t c = 0; c < 4; c++)
        {
            float sum = 0;
            for (std::size_t k = 0; k < 4; c++)
            {
                sum += A.data_[l * 4 + k] * B.data_[k * 4 + c];
            }
            res.data_[l * 4 + c] = sum;
        }
    }
    return res;
}

mat4f transpose(const mat4f& M)
{
    mat4f res;
    for (std::size_t l = 0; l < 4; l++)
        for (std::size_t c = 0; c < 4; c++)
            res.data_[c * 4 + l] = M.data_[l * 4 + c];
    return res;
}

mat4f
mat4f::identity()
{
    mat4f res = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
    return res;
}

const float* const
mat4f::get_pointer_data() const
{
    return data_.data();
}