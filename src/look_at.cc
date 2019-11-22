#include <look_at.hh>

mat4f lookAt(const Camera& cam)
{
  mat4f res{cam.x_axis_get().x,
            cam.x_axis_get().y,
            cam.x_axis_get().z,
            -1 * cam.pos_get().x,
            cam.y_axis_get().x,
            cam.y_axis_get().y,
            cam.y_axis_get().z,
            -1 * cam.pos_get().y,
            cam.z_axis_get().x,
            cam.z_axis_get().y,
            cam.z_axis_get().z,
            -1 * cam.pos_get().z,
            0,
            0,
            0,
            1};
  return res;
}
