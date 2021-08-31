#ifndef _LOADER_H_
#define _LOADER_H_

#include "../vector.h"

#define MAX_VERTICES 100000

typedef struct Object3d {
  int VERTEX_COUNT;
  Vec3* VERTICES;
  Vec3* NORMALS;
  Vec2* TEX_COORDS;
} Object3d;

extern Object3d load_obj(char* path, int faces);

#endif