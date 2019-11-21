#include <cmath>

#include "vec3f.hh"

vec3f::vec3f()
    : x(0)
    , y(0)
    , z(0)
{}

vec3f::vec3f(float _x, float _y, float _z)
    : x(_x)
    , y(_y)
    , z(_z)
{}

vec3f::vec3f(const vec3f& v)
    : x(v.x)
    , y(v.y)
    , z(v.z)
{}

vec3f::~vec3f() {}

vec3f&
vec3f::operator=(const vec3f& v)
{
    x = v.x;
    y = v.y;
    z = v.z;
    return *this;
}

float norm(const vec3f& v)
{
    return std::sqrt(dot(v, v));
}

float dist(const vec3f& u, const vec3f& v)
{
    return norm(u - v);
}

float dot(const vec3f& u, const vec3f& v)
{
    return u.x * v.x + u.y * v.y + u.z * v.z;
}

vec3f cross(const vec3f& u, const vec3f& v)
{
    return vec3f(
        u.y * v.z - u.z * v.y,
        u.z * v.x - u.x * v.z,
        u.x * v.y - u.y * v.x
    );
}

vec3f operator+(const vec3f& u, const vec3f& v)
{
    return vec3f(u.x + v.x, u.y + v.y, u.z + v.z);
}

vec3f operator-(const vec3f& u, const vec3f& v)
{
    return u + -1 * v;
}

vec3f operator*(const vec3f& v, float e)
{
    return vec3f(e * v.x, e * v.y, e * v.z);
}

vec3f operator*(float e, const vec3f& v)
{
    return v * e;
}

std::ostream& operator<<(std::ostream& out, const vec3f& v)
{
    out << "[" << v.x << " " << v.y << " " << v.z << "]";
    return out;
}