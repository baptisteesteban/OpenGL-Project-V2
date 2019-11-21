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