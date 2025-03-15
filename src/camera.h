#ifndef CAMERA_H
#define CAMERA_H

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "vec3f.h"
#include "ppm.h"
#include "mesh.h"

typedef struct {
  Vec3f position;
  Vec3f up;
  Vec3f target;
  float fov;
} Camera;

Camera init_camera(Vec3f position, Vec3f up, Vec3f target, float fov);
void render_mesh(SDL_Renderer* restrict render, const Camera* restrict cam, const Mesh* restrict mesh) ;

#endif //CAMERA_H
