#ifndef CAMERA_H
#define CAMERA_H

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
void render_mesh(const Camera* restrict cam, const Mesh* restrict mesh, const PPMFile* restrict buffer) ;

#endif //CAMERA_H
