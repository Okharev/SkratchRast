#ifndef MAT4F_H
#define MAT4F_H

#include "containers/dyn_arr.h"
#include "vec3f.h"
#include "vec4f.h"

typedef struct {
  alignas(16) float mat[4][4];
} Mat4f;

DYN_ARR_TYPE(Mat4f, Mat4f);

Mat4f mat4f_identity();
void mat4f_multiply_out(const Mat4f* const first, const Mat4f* const second, Mat4f* const out);
Mat4f mat4f_multiply(const Mat4f* const first, const Mat4f* const second);
Vec4f mat4f_multiply_vec4f(const Mat4f* const mat, const Vec4f* const vec);
Mat4f mat4f_rotateX(float const angle);
Mat4f mat4f_rotateY(float const angle);
Mat4f mat4f_rotateZ(float const angle);
// Mat4f mat4f_rotateXYZ(Vec3f* eulers);
Mat4f mat4f_scaling(const Vec3f* const scalings);
Mat4f mat4f_translate(const Vec3f* const translation);
Mat4f mat4f_projection(float const fov, float const aspect, float const near, float const far);
Vec4f mat4f_apply_projection(const Mat4f* const project, const Vec4f* const point);

void mat4f_print(const Mat4f* const m);

#endif
