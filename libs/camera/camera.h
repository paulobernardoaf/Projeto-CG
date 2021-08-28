#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "../vector.h"

typedef struct Camera {
  Vec3 position;
  Vec3 rotation;
} Camera;

extern void initializeCamera(Camera* cam);

extern void setupCamera(Camera* cam);

extern Vec3 forward(Camera* cam);

extern Vec3 up(Camera* cam);

extern Vec3 right(Camera* cam);

#endif