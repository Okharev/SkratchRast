#ifndef CAMERA_H
#define CAMERA_H

#include "vec3f.h"

typedef struct {
  Vec3f position;
  Vec3f up;
  Vec3f target;
  float fov;
} Camera;

Camera init_camera(const Vec3f* restrict position, const Vec3f* restrict up, const Vec3f* restrict target, float fov);

#endif //CAMERA_H
