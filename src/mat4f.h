#ifndef MAT4F_H
#define MAT4F_H

#include <stddef.h>
#include <stdint.h>

#include "vec3f.h"
#include "vec4f.h"

typedef struct {
  float mat[4][4];
} Mat4f;

Mat4f mat4f_identity();
Mat4f mat4f_multiply(Mat4f* const first, Mat4f* const second);
Vec4f mat4f_multiply_vec4f(Mat4f* const mat, Vec4f* const vec);
Mat4f mat4f_rotateX(float const angle);
Mat4f mat4f_rotateY(float const angle);
Mat4f mat4f_rotateZ(float const angle);
// Mat4f mat4f_rotateXYZ(Vec3f* eulers);
Mat4f mat4f_scaling(Vec3f* const scalings);
Mat4f mat4f_translate(Vec3f* const translation);
Mat4f mat4f_projection(float const fov, float const aspect_ratio, float const far, float const near);
Vec4f mat4f_apply_projection(Mat4f* const projection, Vec4f* const point);

void mat4f_print(Mat4f* const m);

#endif
