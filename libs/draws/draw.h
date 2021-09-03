#ifndef _DRAW_H_
#define _DRAW_H_

#include "../vector.h"
#include "../colors.h"
#include "../loader/loader.h"

#define ZFAR (float)10e3

typedef struct Object {
  float width, height, depth;
} Object;

typedef struct Rotation {
  float degrees;
  Vec3 axis;
} Rotation;

extern void draw_axis(int x, int y, int z);

extern void draw_grid(int n, int m);

extern void buildKitchen(Object kitchen);

extern void buildBlock(Object block, Color color);

extern void buildFace(Vec3 vertices[], Color color);

extern void buildDoor(Object kitchen, float doorAngle);

extern void buildWindow(Object kitchen, float windowAngle);

extern void buildObject(Object3d object, int faces);

extern void buildFridge(Object3d fridge, int faces);

extern void buildMicrowave(Object3d microwave, int faces);

extern void buildStove(Object3d stove, int faces);

extern void buildTap(Object3d tap, int faces);

extern void buildChair(Object3d chair, int faces);

extern void buildCabinet(Object kitchen);

extern void buildTable();

#endif