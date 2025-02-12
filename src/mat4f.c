
#include <math.h>
#include <stdint.h>
#include <stdio.h>

#include "containers/dyn_arr.h"
#include "mat4f.h"
#include "vec4f.h"

DYN_ARR_IMPL(Mat4f, Mat4f);

Mat4f mat4f_identity() {
  Mat4f m = {{
    {1.0f, 0.0f, 0.0f, 0.0f},
    {0.0f, 1.0f, 0.0f, 0.0f},
    {0.0f, 0.0f, 1.0f, 0.0f},
    {0.0f, 0.0f, 0.0f, 1.0f}
  }};

  return m;
}

Mat4f mat4f_multiply(const Mat4f* const first, const Mat4f* const second) {
  Mat4f res = {0.0f};

  for (uint8_t i = 0; i < 4; ++i) {
    for (uint8_t j = 0; j < 4; ++j) {
      for (uint8_t k = 0; k < 4; ++k) {
        res.mat[i][j] += first->mat[i][k] * second->mat[k][j];
      }
    }
  }

  return res;
}

Vec4f mat4f_multiply_vec4f(const Mat4f* const mat, const Vec4f* const vec) {
  Vec4f res;

  res.x = mat->mat[0][0] * vec->x + mat->mat[0][1] * vec->y + mat->mat[0][2] * vec->z + mat->mat[0][3] * vec->w;
  res.y = mat->mat[1][0] * vec->x + mat->mat[1][1] * vec->y + mat->mat[1][2] * vec->z + mat->mat[1][3] * vec->w;
  res.z = mat->mat[2][0] * vec->x + mat->mat[2][1] * vec->y + mat->mat[2][2] * vec->z + mat->mat[2][3] * vec->w;
  res.w = mat->mat[3][0] * vec->x + mat->mat[3][1] * vec->y + mat->mat[3][2] * vec->z + mat->mat[3][3] * vec->w;

  return res;
}

Mat4f mat4f_rotateX(float const angle) {
  Mat4f m = {{
    {1.0f, 0.0f, 0.0f, 0.0f},
    {0.0f, cosf(angle), -sinf(angle), 0.0f},
    {0.0f, sinf(angle), cosf(angle), 0.0f},
    {0.0f, 0.0f, 0.0f, 1.0f}
  }};

  return m;
}

Mat4f mat4f_rotateY(float const angle) {
  Mat4f m = {{
    {cosf(angle), 0.0f, sinf(angle), 0.0f},
    {0.0f, 1.0f, 0.0f, 0.0f},
    {-sinf(angle), 0.0f, cosf(angle), 0.0f},
    {0.0f, 0.0f, 0.0f, 1.0f}
  }};
  
  return m;
}

Mat4f mat4f_rotateZ(float const angle) {
  Mat4f m = {{
    {cosf(angle), -sinf(angle), 0.0f, 0.0f},
    {sinf(angle), cosf(angle), 0.0f, 0.0f},
    {0.0f, 0.0f, 1.0f, 0.0f},
    {0.0f, 0.0f, 0.0f, 1.0f}
  }};
    
  return m;
}

Mat4f mat4f_scaling(const Vec3f* const scalings) {
  Mat4f m = {{
    {scalings->x, 0.0f, 0.0f, 0.0f},
    {0.0f, scalings->y, 0.0f, 0.0f},
    {0.0f, 0.0f, scalings->z, 0.0f},
    {0.0f, 0.0f, 0.0f, 1.0f}
  }};

  return m;
}

Mat4f mat4f_translate(const Vec3f* const translation) {
  Mat4f m = {{
    {1.0f, 0.0f, 0.0f, translation->x},
    {0.0f, 1.0f, 0.0f, translation->y},
    {0.0f, 0.0f, 1.0f, translation->z},
    {0.0f, 0.0f, 0.0f, 1.0f}
  }};

  return m;
}

Mat4f mat4f_projection(float const fov, float const aspect, float const near, float const far) {
  float tanHalfFov = tanf(fov / 2.0f);

  Mat4f m = {{
    { 1.0f / (aspect * tanHalfFov), 0.0f, 0.0f, 0.0f },
    { 0.0f, (1.0f / tanHalfFov), 0.0f, 0.0f },
    { 0.0f, 0.0f, ((far + near) / (near - far)), ((2.0f * far * near) / (near - far)) },
    { 0.0f, 0.0f, -1.0f, 0.0f }
  }};
  
  return m;
}

Vec4f mat4f_apply_projection(const Mat4f* const project, const Vec4f* const point) {
  Vec4f transformed = mat4f_multiply_vec4f(project, point);

  if (fabs(transformed.w) > 1e-6) {
      transformed.x /= transformed.w;
      transformed.y /= transformed.w;
      transformed.z = (transformed.z / transformed.w) * 0.5f + 0.5f; 
      transformed.w = 1.0f;
  }

  return transformed;
}

void mat4f_print(const Mat4f* const m) {
  printf("|%.1f, %.1f, %.1f, %.1f|\n|%.1f, %.1f, %.1f, %.1f|\n|%.1f, %.1f, %.1f, %.1f|\n|%.1f, %.1f, %.1f, %.1f|\n",
    m->mat[0][0], m->mat[0][1], m->mat[0][2], m->mat[0][3],
    m->mat[1][0], m->mat[1][1], m->mat[1][2], m->mat[1][3],
    m->mat[2][0], m->mat[2][1], m->mat[2][2], m->mat[2][3],
    m->mat[3][0], m->mat[3][1], m->mat[3][2], m->mat[3][3]
  );
}
