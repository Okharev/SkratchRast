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
void mat4f_multiply_out(const Mat4f* first, const Mat4f* second, Mat4f* out);
Mat4f mat4f_multiply(const Mat4f* first, const Mat4f* second);
Vec4f mat4f_multiply_vec4f(const Mat4f* mat, const Vec4f* vec);
Mat4f mat4f_rotateX(float angle);
Mat4f mat4f_rotateY(float angle);
Mat4f mat4f_rotateZ(float angle);
// Mat4f mat4f_rotateXYZ(Vec3f* eulers);
Mat4f mat4f_scaling(const Vec3f* scalings);
Mat4f mat4f_translate(const Vec3f* translation);
Mat4f mat4f_projection(float fov, float aspect, float near, float far);
Vec4f mat4f_apply_projection(const Mat4f* project, const Vec4f* point);

void mat4f_print(const Mat4f* m);

#endif
