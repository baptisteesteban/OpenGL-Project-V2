#ifndef FRUSTUM_HH
# define FRUSTUM_HH

# include <mat4f.hh>

mat4f frustum(float left, float right, float bottom, float top, float near, float far);

#endif /* !FRUSTUM_HH */