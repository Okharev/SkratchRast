#include <math.h>
#include <stdio.h>

#include "containers/dyn_arr.h"
#include "mat4f.h"
#include "vec4f.h"

DYN_ARR_IMPL(Mat4f, Mat4f);

Mat4f mat4f_identity() {
  Mat4f m;
  m.mat[0][0] = 1.0f;
  m.mat[0][1] = 0.0f;
  m.mat[0][2] = 0.0f;
  m.mat[0][3] = 0.0f;

  m.mat[1][0] = 0.0f;
  m.mat[1][1] = 1.0f;
  m.mat[1][2] = 0.0f;
  m.mat[1][3] = 0.0f;

  m.mat[2][0] = 0.0f;
  m.mat[2][1] = 0.0f;
  m.mat[2][2] = 1.0f;
  m.mat[2][3] = 0.0f;

  m.mat[3][0] = 0.0f;
  m.mat[3][1] = 0.0f;
  m.mat[3][2] = 0.0f;
  m.mat[3][3] = 1.0f;

  return m;
}

void mat4f_multiply(const Mat4f* const restrict first, const Mat4f* const restrict second, Mat4f* const restrict out) {
  const float a00 = first->mat[0][0], a01 = first->mat[0][1], a02 = first->mat[0][2], a03 = first->mat[0][3];
  const float a10 = first->mat[1][0], a11 = first->mat[1][1], a12 = first->mat[1][2], a13 = first->mat[1][3];
  const float a20 = first->mat[2][0], a21 = first->mat[2][1], a22 = first->mat[2][2], a23 = first->mat[2][3];
  const float a30 = first->mat[3][0], a31 = first->mat[3][1], a32 = first->mat[3][2], a33 = first->mat[3][3];

  const float b00 = second->mat[0][0], b01 = second->mat[0][1], b02 = second->mat[0][2], b03 = second->mat[0][3];
  const float b10 = second->mat[1][0], b11 = second->mat[1][1], b12 = second->mat[1][2], b13 = second->mat[1][3];
  const float b20 = second->mat[2][0], b21 = second->mat[2][1], b22 = second->mat[2][2], b23 = second->mat[2][3];
  const float b30 = second->mat[3][0], b31 = second->mat[3][1], b32 = second->mat[3][2], b33 = second->mat[3][3];

  out->mat[0][0] = a00 * b00 + a01 * b10 + a02 * b20 + a03 * b30;
  out->mat[0][1] = a00 * b01 + a01 * b11 + a02 * b21 + a03 * b31;
  out->mat[0][2] = a00 * b02 + a01 * b12 + a02 * b22 + a03 * b32;
  out->mat[0][3] = a00 * b03 + a01 * b13 + a02 * b23 + a03 * b33;

  out->mat[1][0] = a10 * b00 + a11 * b10 + a12 * b20 + a13 * b30;
  out->mat[1][1] = a10 * b01 + a11 * b11 + a12 * b21 + a13 * b31;
  out->mat[1][2] = a10 * b02 + a11 * b12 + a12 * b22 + a13 * b32;
  out->mat[1][3] = a10 * b03 + a11 * b13 + a12 * b23 + a13 * b33;

  out->mat[2][0] = a20 * b00 + a21 * b10 + a22 * b20 + a23 * b30;
  out->mat[2][1] = a20 * b01 + a21 * b11 + a22 * b21 + a23 * b31;
  out->mat[2][2] = a20 * b02 + a21 * b12 + a22 * b22 + a23 * b32;
  out->mat[2][3] = a20 * b03 + a21 * b13 + a22 * b23 + a23 * b33;

  out->mat[3][0] = a30 * b00 + a31 * b10 + a32 * b20 + a33 * b30;
  out->mat[3][1] = a30 * b01 + a31 * b11 + a32 * b21 + a33 * b31;
  out->mat[3][2] = a30 * b02 + a31 * b12 + a32 * b22 + a33 * b32;
  out->mat[3][3] = a30 * b03 + a31 * b13 + a32 * b23 + a33 * b33;
}

void mat4f_multiply_vec4f(const Vec4f* const restrict in, Vec4f* const restrict out, const Mat4f* const restrict mat) {
  out->x = mat->mat[0][0] * in->x + mat->mat[0][1] * in->y + mat->mat[0][2] * in->z + mat->mat[0][3] * in->w;
  out->y = mat->mat[1][0] * in->x + mat->mat[1][1] * in->y + mat->mat[1][2] * in->z + mat->mat[1][3] * in->w;
  out->z = mat->mat[2][0] * in->x + mat->mat[2][1] * in->y + mat->mat[2][2] * in->z + mat->mat[2][3] * in->w;
  out->w = mat->mat[3][0] * in->x + mat->mat[3][1] * in->y + mat->mat[3][2] * in->z + mat->mat[3][3] * in->w;
}

void mat4f_multiply_vec3f(const Vec3f* const restrict in, Vec3f* const restrict out, const Mat4f* const restrict mat) {
  out->x = mat->mat[0][0] * in->x + mat->mat[0][1] * in->y + mat->mat[0][2] * in->z + mat->mat[0][3] * 1.0f;
  out->y = mat->mat[1][0] * in->x + mat->mat[1][1] * in->y + mat->mat[1][2] * in->z + mat->mat[1][3] * 1.0f;
  out->z = mat->mat[2][0] * in->x + mat->mat[2][1] * in->y + mat->mat[2][2] * in->z + mat->mat[2][3] * 1.0f;
  float const w = mat->mat[3][0] * in->x + mat->mat[3][1] * in->y + mat->mat[3][2] * in->z + mat->mat[3][3] * 1.0f;

  out->x /= w;
  out->y /= w;
  out->z /= w;
}

Mat4f mat4f_rotateX(const float angle) {
  const float sinAngle = sinf(angle);
  const float cosAngle = cosf(angle);

  Mat4f m;
  m.mat[0][0] = 1.0f;
  m.mat[0][1] = 0.0f;
  m.mat[0][2] = 0.0f;
  m.mat[0][3] = 0.0f;

  m.mat[1][0] = 0.0f;
  m.mat[1][1] = cosAngle;
  m.mat[1][2] = -sinAngle;
  m.mat[1][3] = 0.0f;

  m.mat[2][0] = 0.0f;
  m.mat[2][1] = sinAngle;
  m.mat[2][2] = cosAngle;
  m.mat[2][3] = 0.0f;

  m.mat[3][0] = 0.0f;
  m.mat[3][1] = 0.0f;
  m.mat[3][2] = 0.0f;
  m.mat[3][3] = 1.0f;

  return m;
}

Mat4f mat4f_rotateY(const float angle) {
  const float sinAngle = sinf(angle);
  const float cosAngle = cosf(angle);

  Mat4f m;
  m.mat[0][0] = cosAngle;
  m.mat[0][1] = 0.0f;
  m.mat[0][2] = sinAngle;
  m.mat[0][3] = 0.0f;

  m.mat[1][0] = 0.0f;
  m.mat[1][1] = 1.0f;
  m.mat[1][2] = 0.0f;
  m.mat[1][3] = 0.0f;

  m.mat[2][0] = -sinAngle;
  m.mat[2][1] = 0.0f;
  m.mat[2][2] = cosAngle;
  m.mat[2][3] = 0.0f;

  m.mat[3][0] = 0.0f;
  m.mat[3][1] = 0.0f;
  m.mat[3][2] = 0.0f;
  m.mat[3][3] = 1.0f;

  return m;
}

Mat4f mat4f_rotateZ(const float angle) {
  const float sinAngle = sinf(angle);
  const float cosAngle = cosf(angle);

  Mat4f m;
  m.mat[0][0] = cosAngle;
  m.mat[0][1] = -sinAngle;
  m.mat[0][2] = 0.0f;
  m.mat[0][3] = 0.0f;

  m.mat[1][0] = sinAngle;
  m.mat[1][1] = cosAngle;
  m.mat[1][2] = 0.0f;
  m.mat[1][3] = 0.0f;

  m.mat[2][0] = 0.0f;
  m.mat[2][1] = 0.0f;
  m.mat[2][2] = 1.0f;
  m.mat[2][3] = 0.0f;

  m.mat[3][0] = 0.0f;
  m.mat[3][1] = 0.0f;
  m.mat[3][2] = 0.0f;
  m.mat[3][3] = 1.0f;

  return m;
}

Mat4f mat4f_scaling(const Vec3f* restrict const scaling) {
  Mat4f m;
  m.mat[0][0] = scaling->x;
  m.mat[0][1] = 0.0f;
  m.mat[0][2] = 0.0f;
  m.mat[0][3] = 0.0f;

  m.mat[1][0] = 0.0f;
  m.mat[1][1] = scaling->y;
  m.mat[1][2] = 0.0f;
  m.mat[1][3] = 0.0f;

  m.mat[2][0] = 0.0f;
  m.mat[2][1] = 0.0f;
  m.mat[2][2] = scaling->z;
  m.mat[2][3] = 0.0f;

  m.mat[3][0] = 0.0f;
  m.mat[3][1] = 0.0f;
  m.mat[3][2] = 0.0f;
  m.mat[3][3] = 1.0f;

  return m;
}

Mat4f mat4f_translate(const Vec3f* restrict const translation) {
  Mat4f m;
  m.mat[0][0] = 1.0f;
  m.mat[0][1] = 0.0f;
  m.mat[0][2] = 0.0f;
  m.mat[0][3] = translation->x;

  m.mat[1][0] = 0.0f;
  m.mat[1][1] = 1.0f;
  m.mat[1][2] = 0.0f;
  m.mat[1][3] = translation->y;

  m.mat[2][0] = 0.0f;
  m.mat[2][1] = 0.0f;
  m.mat[2][2] = 1.0f;
  m.mat[2][3] = translation->z;

  m.mat[3][0] = 0.0f;
  m.mat[3][1] = 0.0f;
  m.mat[3][2] = 0.0f;
  m.mat[3][3] = 1.0f;

  return m;
}

Mat4f mat4f_look_at(const Vec3f* restrict target) {

}

Mat4f mat4f_projection(const float fov, const float aspect, const float near, const float far) {
  const float tanHalfFov = tanf(fov / 2.0f);

  Mat4f m;
  m.mat[0][0] = 1.0f / (aspect * tanHalfFov);
  m.mat[0][1] = 0.0f;
  m.mat[0][2] = 0.0f;
  m.mat[0][3] = 0.0f;

  m.mat[1][0] = 0.0f;
  m.mat[1][1] = 1.0f / tanHalfFov;
  m.mat[1][2] = 0.0f;
  m.mat[1][3] = 0.0f;

  m.mat[2][0] = 0.0f;
  m.mat[2][1] = 0.0f;
  m.mat[2][2] = (far + near) / (near - far);
  m.mat[2][3] = 2.0f * far * near / (near - far);

  m.mat[3][0] = 0.0f;
  m.mat[3][1] = 0.0f;
  m.mat[3][2] = -1.0f;
  m.mat[3][3] = 0.0f;

  return m;
}

void mat4f_print(const Mat4f* restrict const m) {
  // clang-format off
  printf(
      "|%.1f, %.1f, %.1f, %.1f|\n|%.1f, %.1f, %.1f, %.1f|\n|%.1f, %.1f, %.1f, %.1f|\n|%.1f, %.1f, %.1f, %.1f|\n",
      m->mat[0][0], m->mat[0][1], m->mat[0][2], m->mat[0][3],
      m->mat[1][0], m->mat[1][1], m->mat[1][2], m->mat[1][3],
      m->mat[2][0], m->mat[2][1], m->mat[2][2], m->mat[2][3],
      m->mat[3][0], m->mat[3][1], m->mat[3][2], m->mat[3][3]
  );
  // clang-format on
}
