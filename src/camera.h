#ifndef CAMERA_H
#define CAMERA_H

#include <SDL3/SDL.h>

#include "vec3f.h"
#include "ppm.h"
#include "mesh.h"

typedef struct {
  Vec3f position;
  Vec3f up;
  Vec3f target;
  float fov;
} Camera;

///
/// @param position
/// @param up
/// @param target
/// @param fov
/// @return
Camera init_camera(Vec3f position, Vec3f up, Vec3f target, float fov);

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
