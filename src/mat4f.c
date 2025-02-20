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

void mat4f_multiply_out(const Mat4f* const restrict first, const Mat4f* const restrict second, Mat4f* const restrict out) {
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

Mat4f mat4f_multiply(const Mat4f* restrict const first, const Mat4f* restrict const second) {
  Mat4f m;
  const float a00 = first->mat[0][0], a01 = first->mat[0][1], a02 = first->mat[0][2], a03 = first->mat[0][3];
  const float a10 = first->mat[1][0], a11 = first->mat[1][1], a12 = first->mat[1][2], a13 = first->mat[1][3];
  const float a20 = first->mat[2][0], a21 = first->mat[2][1], a22 = first->mat[2][2], a23 = first->mat[2][3];
  const float a30 = first->mat[3][0], a31 = first->mat[3][1], a32 = first->mat[3][2], a33 = first->mat[3][3];

  const float b00 = second->mat[0][0], b01 = second->mat[0][1], b02 = second->mat[0][2], b03 = second->mat[0][3];
  const float b10 = second->mat[1][0], b11 = second->mat[1][1], b12 = second->mat[1][2], b13 = second->mat[1][3];
  const float b20 = second->mat[2][0], b21 = second->mat[2][1], b22 = second->mat[2][2], b23 = second->mat[2][3];
  const float b30 = second->mat[3][0], b31 = second->mat[3][1], b32 = second->mat[3][2], b33 = second->mat[3][3];

  m.mat[0][0] = a00 * b00 + a01 * b10 + a02 * b20 + a03 * b30;
  m.mat[0][1] = a00 * b01 + a01 * b11 + a02 * b21 + a03 * b31;
  m.mat[0][2] = a00 * b02 + a01 * b12 + a02 * b22 + a03 * b32;
  m.mat[0][3] = a00 * b03 + a01 * b13 + a02 * b23 + a03 * b33;

  m.mat[1][0] = a10 * b00 + a11 * b10 + a12 * b20 + a13 * b30;
  m.mat[1][1] = a10 * b01 + a11 * b11 + a12 * b21 + a13 * b31;
  m.mat[1][2] = a10 * b02 + a11 * b12 + a12 * b22 + a13 * b32;
  m.mat[1][3] = a10 * b03 + a11 * b13 + a12 * b23 + a13 * b33;

  m.mat[2][0] = a20 * b00 + a21 * b10 + a22 * b20 + a23 * b30;
  m.mat[2][1] = a20 * b01 + a21 * b11 + a22 * b21 + a23 * b31;
  m.mat[2][2] = a20 * b02 + a21 * b12 + a22 * b22 + a23 * b32;
  m.mat[2][3] = a20 * b03 + a21 * b13 + a22 * b23 + a23 * b33;

  m.mat[3][0] = a30 * b00 + a31 * b10 + a32 * b20 + a33 * b30;
  m.mat[3][1] = a30 * b01 + a31 * b11 + a32 * b21 + a33 * b31;
  m.mat[3][2] = a30 * b02 + a31 * b12 + a32 * b22 + a33 * b32;
  m.mat[3][3] = a30 * b03 + a31 * b13 + a32 * b23 + a33 * b33;

  return m;
}

Vec4f mat4f_multiply_vec4f(const Mat4f* restrict const mat, const Vec4f* restrict const vec) {
  Vec4f res;

  res.x = mat->mat[0][0] * vec->x + mat->mat[0][1] * vec->y + mat->mat[0][2] * vec->z + mat->mat[0][3] * vec->w;
  res.y = mat->mat[1][0] * vec->x + mat->mat[1][1] * vec->y + mat->mat[1][2] * vec->z + mat->mat[1][3] * vec->w;
  res.z = mat->mat[2][0] * vec->x + mat->mat[2][1] * vec->y + mat->mat[2][2] * vec->z + mat->mat[2][3] * vec->w;
  res.w = mat->mat[3][0] * vec->x + mat->mat[3][1] * vec->y + mat->mat[3][2] * vec->z + mat->mat[3][3] * vec->w;

  return res;
}

Mat4f mat4f_rotateX(float const angle) {
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

Mat4f mat4f_rotateY(float const angle) {
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

Mat4f mat4f_rotateZ(float const angle) {
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

Mat4f mat4f_scaling(const Vec3f* restrict const scalings) {
  Mat4f m;
  m.mat[0][0] = scalings->x;
  m.mat[0][1] = 0.0f;
  m.mat[0][2] = 0.0f;
  m.mat[0][3] = 0.0f;

  m.mat[1][0] = 0.0f;
  m.mat[1][1] = scalings->y;
  m.mat[1][2] = 0.0f;
  m.mat[1][3] = 0.0f;

  m.mat[2][0] = 0.0f;
  m.mat[2][1] = 0.0f;
  m.mat[2][2] = scalings->z;
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

Mat4f mat4f_projection(float const fov, float const aspect, float const near, float const far) {
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

Vec4f mat4f_apply_projection(const Mat4f* restrict const project, const Vec4f* restrict const point) {
  Vec4f transformed = mat4f_multiply_vec4f(project, point);

  if (fabsf(transformed.w) > 1e-6) {
    transformed.x /= transformed.w;
    transformed.y /= transformed.w;
    transformed.z = (transformed.z / transformed.w) * 0.5f + 0.5f;
    transformed.w = 1.0f;
  }

  return transformed;
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
