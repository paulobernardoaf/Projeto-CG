#include "camera.h"
#include "../vector.h"

#include <math.h>
#include <ctype.h>

#include <GL/gl.h>
#include <GL/freeglut.h>

// Constants

const float DEG2RAD = M_PI / 180.0f;
const float RAD2DEG = 180.0f / M_PI;

void initializeCamera(Camera* cam) {
  cam->position = (Vec3){ 2.0f, 2.3f, 2.0f };
  cam->rotation = (Vec3){ 0.0f, 180.0f, 0.0f };
}

void setupCamera(Camera* cam) {
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  // View matrix
  Vec3 fwd = forward(cam);
  Vec3 u = up(cam);
  Vec3 eye = cam->position;
  Vec3 center = { eye.x + fwd.x, eye.y + fwd.y, eye.z + fwd.z };

  gluLookAt(eye.x, eye.y, eye.z, center.x, center.y, center.z, u.x, u.y, u.z);
}

// Math utils

Vec3 forward(Camera* cam) {
  Vec3 v;
  float a = cam->rotation.x * DEG2RAD;
  float b = cam->rotation.y * DEG2RAD;
  float c = cam->rotation.z * DEG2RAD;

  v.x = -(sin(c) * sin(a) + cos(c) * sin(b) * cos(a));
  v.y = -(-cos(c) * sin(a) + sin(c) * sin(b) * cos(a));
  v.z = -(cos(b) * cos(a));

  return v;
}

Vec3 up(Camera* cam) {
  Vec3 v;
  float a = cam->rotation.x * DEG2RAD;
  float b = cam->rotation.y * DEG2RAD;
  float c = cam->rotation.z * DEG2RAD;

  v.x = -sin(c) * cos(a) + cos(c) * sin(b) * sin(a);
  v.y = cos(c) * cos(a) + sin(c) * sin(b) * sin(a);
  v.z = cos(b) * sin(a);

  return v;
}

Vec3 right(Camera* cam) {
  Vec3 v;
  float a = cam->rotation.x * DEG2RAD;
  float b = cam->rotation.y * DEG2RAD;
  float c = cam->rotation.z * DEG2RAD;

  v.x = cos(c) * cos(b);
  v.y = sin(c) * cos(b);
  v.z = -sin(b);

  return v;
}