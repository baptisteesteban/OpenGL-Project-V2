#ifndef CAMERA_HH
# define CAMERA_HH

# include <ostream>
# include "vec3f.hh"

class Camera
{
public:
    Camera() = delete;
    Camera(const vec3f& pos, const vec3f& x_axis, const vec3f& y_axis);

    const vec3f& x_axis_get() const;
    const vec3f& y_axis_get() const;
    const vec3f& z_axis_get() const;
    const vec3f& pos_get() const;

    void x_axis_set(const vec3f& e);
    void y_axis_set(const vec3f& e);
    void z_axis_set(const vec3f& e);
    void pos_set(const vec3f& e);

    friend std::ostream& operator<<(std::ostream& out, const Camera& cam);

private:
    vec3f pos_;
    vec3f x_axis_;
    vec3f y_axis_;
    vec3f z_axis_;
};

#endif /* !CAMERA_HH */