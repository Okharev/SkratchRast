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
void mat4f_multiply(const Mat4f* restrict first, const Mat4f* restrict second, Mat4f* restrict out);
void mat4f_multiply_vec4f(const Vec4f* restrict in, Vec4f* restrict out, const Mat4f* restrict mat);
void mat4f_multiply_vec3f(const Vec3f* restrict in, Vec3f* restrict out, const Mat4f* restrict mat);
Mat4f mat4f_rotateX(float angle);
Mat4f mat4f_rotateY(float angle);
Mat4f mat4f_rotateZ(float angle);
// Mat4f mat4f_rotateXYZ(Vec3f* restrict eulers);
Mat4f mat4f_scaling(const Vec3f* restrict scaling);
Mat4f mat4f_translate(const Vec3f* restrict translation);
Mat4f mat4f_projection(float fov, float aspect, float near, float far);

void mat4f_print(const Mat4f* restrict m);

#endif
