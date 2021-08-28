#ifndef _DRAW_H_
#define _DRAW_H_

#include "../vector.h"
#include "../colors.h"

#define ZFAR (float)10e3

typedef struct Object {
  float width, height, depth;
} Object;

typedef struct Rotation {
  float degrees;
  Vec3 axis;
} Rotation;

extern void draw_axis(int x, int y, int z);

extern void draw_grid(int n);

extern void drawRoom();

extern void buildWall(Vec3 position, Object scale, Rotation rotation, Color color);

#endif