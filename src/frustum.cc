#include <frustum.hh>

mat4f frustum(float left, float right, float bottom, float top, float near, float far)
{
    float A = (right + left) / (right - left);
    float B = (top + bottom) / (top - bottom);
    float C = (-1 * (far + near) / (far - near));
    float D = (-2 * far * near) / (far - near);
    return mat4f{
        (2 * near) / (right - left), 0, A, 0,
        0, (2 * near) / (top - bottom), B, 0,
        0, 0, C, D,
        0, 0, -1, 0
    };
}
