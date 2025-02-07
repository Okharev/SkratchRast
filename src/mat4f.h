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
Mat4f mat4f_multiply(Mat4f* first, Mat4f* second);
Vec4f mat4f_multiply_vec4f(Mat4f* mat, Vec4f* vec);
Mat4f mat4f_rotateX(float angle);
Mat4f mat4f_rotateY(float angle);
Mat4f mat4f_rotateZ(float angle);
// Mat4f mat4f_rotateXYZ(Vec3f* eulers);
Mat4f mat4f_scaling(Vec3f* scalings);
Mat4f mat4f_translate(Vec3f* translation);
Mat4f mat4f_projection(Vec3f* translation);

void mat4f_print(Mat4f* m);

#endif
