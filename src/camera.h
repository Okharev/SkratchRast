#ifndef CAMERA_H
#define CAMERA_H

#include <SDL3/SDL.h>

#include "vec3f.h"
#include "ppm.h"
#include "mesh.h"
#include "transform.h"

// TODO Add caching mechanism for view matrix and projection matrix
typedef struct {
  Transform transform;
  Mat4f proj;
  Mat4f view;
  Vec3f up;
  float fov;
} Camera;

///
/// @param position
/// @param up
/// @param target
/// @param fov
/// @return
Camera init_camera(Vec3f position, Vec4f quaternion, Vec3f up, float fov);

void look_at(Camera* restrict cam, const Vec3f* target);

/// TODO rafcator into smaller function for clarity
/// TODO document this
/// TODO Add Edges drawing
/// TODO Add Faces drawing
/// TODO Add simple shading
/// @param renderer
/// @param cam
/// @param mesh
void render_mesh(SDL_Renderer* restrict renderer, const Camera* restrict cam, const Mesh* restrict mesh);

#endif //CAMERA_H
