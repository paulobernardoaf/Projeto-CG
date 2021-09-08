#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "../vector.h"

typedef struct Camera {
  Vec3 position;
  Vec3 forward;
  Vec3 up;
} Camera;

extern void initializeCamera(Camera* cam);

extern void setupCamera(Camera* cam);

extern Vec3 forward(Camera* cam);

extern Vec3 up(Camera* cam);

extern Vec3 right(Camera* cam);

extern void move_forward(Camera* cam);

extern void move_backward(Camera* cam);

extern void move_right(Camera* cam);

extern void move_left(Camera* cam);

extern Vec3 crossProduct(Vec3 a, Vec3 b);

#endif