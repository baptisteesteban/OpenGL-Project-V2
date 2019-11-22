#ifndef VEC3F_HH
#define VEC3F_HH

#include <ostream>

struct vec3f
{
  vec3f();
  vec3f(float _x, float _y, float _z);
  vec3f(const vec3f&);
  ~vec3f();
  vec3f& operator=(const vec3f&);
  float  x;
  float  y;
  float  z;
};

float norm(const vec3f&);
float dist(const vec3f&, const vec3f&);
float dot(const vec3f&, const vec3f&);
vec3f cross(const vec3f&, const vec3f&);
vec3f operator+(const vec3f&, const vec3f&);
vec3f operator-(const vec3f&, const vec3f&);
vec3f operator*(const vec3f&, float);
vec3f operator*(float, const vec3f&);

std::ostream& operator<<(std::ostream&, const vec3f& v);

#endif /* VEC3F_HH */