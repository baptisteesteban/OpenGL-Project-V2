#include <camera.hh>

Camera::Camera(const vec3f& pos, const vec3f& x_axis, const vec3f& y_axis)
  : pos_(pos)
  , x_axis_(x_axis)
  , y_axis_(y_axis)
  , z_axis_(cross(x_axis, y_axis))
{
}

const vec3f& Camera::x_axis_get() const
{
  return x_axis_;
}

const vec3f& Camera::y_axis_get() const
{
  return y_axis_;
}

const vec3f& Camera::z_axis_get() const
{
  return z_axis_;
}

const vec3f& Camera::pos_get() const
{
  return pos_;
}

void Camera::x_axis_set(const vec3f& e)
{
  x_axis_ = e;
}

void Camera::y_axis_set(const vec3f& e)
{
  y_axis_ = e;
}

void Camera::z_axis_set(const vec3f& e)
{
  z_axis_ = e;
}

void Camera::pos_set(const vec3f& e)
{
  pos_ = vec3f(e);
}

std::ostream& operator<<(std::ostream& out, const Camera& cam)
{
  out << "Camera at " << cam.pos_ << "\n";
  out << "x axis " << cam.x_axis_ << "\n";
  out << "y axis " << cam.y_axis_ << "\n";
  out << "z axis " << cam.z_axis_ << "\n";
  return out;
}
