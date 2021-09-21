#ifndef _DRAW_H_
#define _DRAW_H_

#include "../vector.h"
#include "../colors.h"
#include "../loader/loader.h"

#define ZFAR (float)10e3

typedef struct Object {
  float width, height, depth;
} Object;

extern void buildKitchen(Object kitchen);

extern void buildBlock(Object block, Color color);

extern void buildFace(Vec3 vertices[], Color color, Vec2 texCoords[]);

extern void buildDoor(Object kitchen, float doorAngle, Texture texture);

extern void buildWindow(Object kitchen, float windowAngle);

extern void buildObject(Object3d object, int faces);

extern void buildFridge(Object3d fridge, int faces, Texture texture);

extern void buildMicrowave(Object3d microwave, int faces, Texture texture);

extern void buildStove(Object3d stove, int faces, Texture texture);

extern void buildTap(Object3d tap, int faces, Texture texture);

extern void buildChair(Object3d chair, int faces, Texture texture);

extern void buildCabinet(Object kitchen);

extern void buildTable(Texture texture);

extern void buildLamp(Object3d lamp, int faces, Texture texture);

extern void buildFan(Object3d fan, int faces, float rotation, Texture texture);

extern void buildPaint(Texture texture);

#endif