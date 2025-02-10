#include <math.h>
#include <stdint.h>
#include <stdio.h>

#include "mat4f.h"
#include "vec4f.h"

// Create an identity matrix
Mat4f mat4f_identity() {
  // clang-format off
  Mat4f m = {
    {
      {1.0f, 0.0f, 0.0f, 0.0f},
      {0.0f, 1.0f, 0.0f, 0.0f},
      {0.0f, 0.0f, 1.0f, 0.0f},
      {0.0f, 0.0f, 0.0f, 1.0f}
    }
  };
  // clang-format on

  return m;
}

// Multiply two 4x4 matrices
Mat4f mat4f_multiply(const Mat4f* const first, const Mat4f* const second) {
  // clang-format off
  Mat4f res = { { {0.0f, 0.0f, 0.0f, 0.0f},
                  {0.0f, 0.0f, 0.0f, 0.0f},
                  {0.0f, 0.0f, 0.0f, 0.0f},
                  {0.0f, 0.0f, 0.0f, 0.0f} } };
  // clang-format on

  for (uint8_t i = 0; i < 4; ++i) {
    for (uint8_t j = 0; j < 4; ++j) {
      for (uint8_t k = 0; k < 4; ++k) {
        res.mat[i][j] += first->mat[i][k] * second->mat[k][j];
      }
    }
  }

  return res;
}

// Multiply a 4x4 matrix with a 4D vector
Vec4f mat4f_multiply_vec4f(const Mat4f* const mat, const Vec4f* const vec) {
  Vec4f res = {0.0f, 0.0f, 0.0f, 0.0f};
  // clang-format off
  res.x = mat->mat[0][0] * vec->x +
          mat->mat[0][1] * vec->y +
          mat->mat[0][2] * vec->z +
          mat->mat[0][3] * vec->w;

  res.y = mat->mat[1][0] * vec->x +
          mat->mat[1][1] * vec->y +
          mat->mat[1][2] * vec->z +
          mat->mat[1][3] * vec->w;

  res.z = mat->mat[2][0] * vec->x +
          mat->mat[2][1] * vec->y +
          mat->mat[2][2] * vec->z +
          mat->mat[2][3] * vec->w;

  res.w = mat->mat[3][0] * vec->x +
          mat->mat[3][1] * vec->y +
          mat->mat[3][2] * vec->z +
          mat->mat[3][3] * vec->w;
  // clang-format on

  return res;
}

// Create a rotation matrix about the X-axis
Mat4f mat4f_rotateX(float const angle) {
  // clang-format off
  Mat4f m = {
    {
      {1.0f,         0.0f,         0.0f,  0.0f},
      {0.0f,  cosf(angle), -sinf(angle),  0.0f},
      {0.0f,  sinf(angle),  cosf(angle),  0.0f},
      {0.0f,      0.0f,            0.0f,       1.0f}
    }
  };
  // clang-format on

  return m;
}

// Create a rotation matrix about the Y-axis
Mat4f mat4f_rotateY(float const angle) {
  // clang-format off
  Mat4f m = {
    {
      { cosf(angle), 0.0f, sinf(angle), 0.0f},
      {        0.0f, 1.0f,        0.0f, 0.0f},
      {-sinf(angle), 0.0f, cosf(angle), 0.0f},
      {        0.0f, 0.0f,        0.0f, 1.0f}
    }
  };
  // clang-format on

  return m;
}

// Create a rotation matrix about the Z-axis
Mat4f mat4f_rotateZ(float const angle) {
  // clang-format off
  Mat4f m = {
    {
      {cosf(angle), -sinf(angle), 0.0f, 0.0f},
      {sinf(angle),  cosf(angle), 0.0f, 0.0f},
      {    0.0f,         0.0f,   1.0f, 0.0f},
      {    0.0f,         0.0f,   0.0f, 1.0f}
    }
  };
  // clang-format on

  return m;
}

// Create a scaling matrix from a 3D vector
Mat4f mat4f_scaling(const Vec3f* const scalings) {
  // clang-format off
  Mat4f m = {
    {
      {scalings->x, 0.0f,       0.0f,      0.0f},
      {0.0f,       scalings->y, 0.0f,      0.0f},
      {0.0f,       0.0f,       scalings->z,0.0f},
      {0.0f,       0.0f,       0.0f,      1.0f}
    }
  };
  // clang-format on

  return m;
}

// Create a translation matrix from a 3D vector
Mat4f mat4f_translate(const Vec3f* const translation) {
  // clang-format off
  Mat4f m = {
    {
      {1.0f, 0.0f, 0.0f, translation->x},
      {0.0f, 1.0f, 0.0f, translation->y},
      {0.0f, 0.0f, 1.0f, translation->z},
      {0.0f, 0.0f, 0.0f, 1.0f}
    }
  };
  // clang-format on

  return m;
}

// Create a perspective projection matrix
Mat4f mat4f_projection(float const fov, float const aspect_ratio, float const far, float const near) {
  // Convert fov to radians and compute the scale factor
  float fovRad = fov * (3.1415f / 180.0f);
  float scale = 1.0f / tanf(fovRad / 2.0f);

  // clang-format off
  Mat4f projection = {
    {
      {0.0f, 0.0f, 0.0f, 0.0f},
      {0.0f, 0.0f, 0.0f, 0.0f},
      {0.0f, 0.0f, 0.0f, 0.0f},
      {0.0f, 0.0f, 0.0f, 0.0f}
    }
  };
  // clang-format on

  projection.mat[0][0] = scale / aspect_ratio;
  projection.mat[1][1] = scale;
  projection.mat[2][2] = -(far + near) / (far - near);
  projection.mat[2][3] = -(2 * far * near) / (far - near);
  projection.mat[3][2] = -1.0f;
  projection.mat[3][3] = 0.0f;

  return projection;
}

// Apply the projection to a 4D vector (including perspective division)
Vec4f mat4f_apply_projection(const Mat4f* const projection, const Vec4f* const point) {
  Vec4f res = mat4f_multiply_vec4f(projection, point);

  // Perform perspective division
  res.x /= res.w;
  res.y /= res.w;
  res.z /= res.w;
  res.w = 1.0f;  // or leave as-is if you prefer

  return res;
}

// Print a 4x4 matrix
void mat4f_print(const Mat4f* m) {
  // clang-format off
  printf("|%.1f, %.1f, %.1f, %.1f|\n"
         "|%.1f, %.1f, %.1f, %.1f|\n"
         "|%.1f, %.1f, %.1f, %.1f|\n"
         "|%.1f, %.1f, %.1f, %.1f|\n",
         m->mat[0][0], m->mat[0][1], m->mat[0][2], m->mat[0][3],
         m->mat[1][0], m->mat[1][1], m->mat[1][2], m->mat[1][3],
         m->mat[2][0], m->mat[2][1], m->mat[2][2], m->mat[2][3],
         m->mat[3][0], m->mat[3][1], m->mat[3][2], m->mat[3][3]);
  // clang-format on
}
