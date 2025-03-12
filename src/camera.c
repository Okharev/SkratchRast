//
// Created by okharev on 12/03/25.
//

#include "camera.h"

#include "helpers.h"
#include "mat4f.h"

static float deg_to_rad(const float radians) {
  return radians * (180.0f / PI_F);
}

///
/// @param position The camera location in world space
/// @param up where is the camera "up" vector (usually Y)
/// @param target where the camera is looking at (Pitch and Yaw)
/// @param fov The field of view in degrees
/// @return the final camera
Camera init_camera(const Vec3f* const restrict position, const Vec3f* const restrict up, const Vec3f* const restrict target, const float fov) {
  const Mat4f proj = mat4f_projection(deg_to_rad(fov), 16.0f / 9.0f, 0.0001f, 10000.0f);
  const Mat4f view = mat4f_translate(&(Vec3f){.x = -position->x, .y = -position->y, .z = -position->z});

}