#ifndef _LOADER_H_
#define _LOADER_H_

#include <limits.h>

#include "../vector.h"
#include "../colors.h"

#define MAX_VERTICES (size_t)210000

typedef struct Object3d {
  int VERTEX_COUNT;
  Vec3* VERTICES;
  Vec3* NORMALS;
  Vec2* TEX_COORDS;
} Object3d;

typedef struct Texture {
  int id, width, height, nrChannels;
  unsigned char* data;
} Texture;

typedef struct Material {
  Color ambient, diffuse, specular;
  float shininess;
} Material;

extern Object3d load_obj(char* path, int faces);

extern void load_texture(char* path, Texture* texture);

extern void setupTexture(Texture* texture);

extern void enableMaterial(Material mtl);

extern void enableDye(Material mtl);

#endif