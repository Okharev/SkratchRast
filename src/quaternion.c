#ifndef QUATERNION_H
#define QUATERNION_H
#include <math.h>

#include "mat4f.h"

Vec4f mat4f_to_quat(const Mat4f* const restrict rotation) {
  Vec4f q;
  const float trace = rotation->mat[0][0] + rotation->mat[1][1] + rotation->mat[2][2];
  if (trace > 0.0f) {
    const float s = sqrtf(trace + 1.0f) * 2.0f;
    q.w = 0.25f * s;
    q.x = (rotation->mat[2][1] - rotation->mat[1][2]) / s;
    q.y = (rotation->mat[0][2] - rotation->mat[2][0]) / s;
    q.z = (rotation->mat[1][0] - rotation->mat[0][1]) / s;
  } else if (rotation->mat[0][0] > rotation->mat[1][1] && rotation->mat[0][0] > rotation->mat[2][2]) {
    const float s = sqrtf(1.0f + rotation->mat[0][0] - rotation->mat[1][1] - rotation->mat[2][2]) * 2.0f;
    q.w = (rotation->mat[2][1] - rotation->mat[1][2]) / s;
    q.x = 0.25f * s;
    q.y = (rotation->mat[0][1] + rotation->mat[1][0]) / s;
    q.z = (rotation->mat[0][2] + rotation->mat[2][0]) / s;
  } else if (rotation->mat[1][1] > rotation->mat[2][2]) {
    const float s = sqrtf(1.0f + rotation->mat[1][1] - rotation->mat[0][0] - rotation->mat[2][2]) * 2.0f;
    q.w = (rotation->mat[0][2] - rotation->mat[2][0]) / s;
    q.x = (rotation->mat[0][1] + rotation->mat[1][0]) / s;
    q.y = 0.25f * s;
    q.z = (rotation->mat[1][2] + rotation->mat[2][1]) / s;
  } else {
    const float s = sqrtf(1.0f + rotation->mat[2][2] - rotation->mat[0][0] - rotation->mat[1][1]) * 2.0f;
    q.w = (rotation->mat[1][0] - rotation->mat[0][1]) / s;
    q.x = (rotation->mat[0][2] + rotation->mat[2][0]) / s;
    q.y = (rotation->mat[1][2] + rotation->mat[2][1]) / s;
    q.z = 0.25f * s;
  }
  return q;
}


inline Vec4f quat_look_at(const Vec3f* const restrict origin, const Vec3f* const restrict target, const Vec3f* const restrict up) {
  const Vec3f subbed    = vec3f_substract(target, origin);
  const Vec3f forward   = vec3f_normalize(&subbed);
  const Vec3f normalized = vec3f_cross(up, &forward);
  const Vec3f right     = vec3f_normalize(&normalized);
  const Vec3f corrected = vec3f_cross(&right, &forward);

  const Mat4f view = (Mat4f){
    .mat = {
      {right.x,    right.y,    right.z,    0.0f},
      {corrected.x,corrected.y,corrected.z,0.0f},
      {-forward.x, -forward.y, -forward.z, 0.0f},
      {0.0f,       0.0f,       0.0f,       1.0f}
    }
  };

  // Convert the rotation matrix to a quaternion.
  return mat4f_to_quat(&view);
}

Mat4f quat_to_mat4f(const Vec4f* const restrict q) {
  Mat4f m;

  // Precompute reused values.
  const float xx = q->x * q->x;
  const float yy = q->y * q->y;
  const float zz = q->z * q->z;
  const float xy = q->x * q->y;
  const float xz = q->x * q->z;
  const float yz = q->y * q->z;
  const float wx = q->w * q->x;
  const float wy = q->w * q->y;
  const float wz = q->w * q->z;

  // First row
  m.mat[0][0] = 1.0f - 2.0f * (yy + zz);
  m.mat[0][1] = 2.0f * (xy - wz);
  m.mat[0][2] = 2.0f * (xz + wy);
  m.mat[0][3] = 0.0f;

  // Second row
  m.mat[1][0] = 2.0f * (xy + wz);
  m.mat[1][1] = 1.0f - 2.0f * (xx + zz);
  m.mat[1][2] = 2.0f * (yz - wx);
  m.mat[1][3] = 0.0f;

  // Third row
  m.mat[2][0] = 2.0f * (xz - wy);
  m.mat[2][1] = 2.0f * (yz + wx);
  m.mat[2][2] = 1.0f - 2.0f * (xx + yy);
  m.mat[2][3] = 0.0f;

  // Fourth row (homogeneous coordinate)
  m.mat[3][0] = 0.0f;
  m.mat[3][1] = 0.0f;
  m.mat[3][2] = 0.0f;
  m.mat[3][3] = 1.0f;

  return m;
}
#endif // QUATERNION_H