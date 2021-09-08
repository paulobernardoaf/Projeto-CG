#include "camera.h"
#include "../vector.h"
#include <stdio.h>

#include <math.h>
#include <ctype.h>

#include <GL/gl.h>
#include <GL/freeglut.h>


void initializeCamera(Camera* cam) {
  cam->position = (Vec3){ 3.0f, 2.3f, 4.0f };
  cam->forward = (Vec3){ 0.0f, 0.0f, 1.0f };
  cam->up = (Vec3){ 0.0f, 1.0f, 0.0f };
}

void setupCamera(Camera* cam) {
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  Vec3 up = cam->up;
  Vec3 eye = cam->position;
  Vec3 center = { eye.x + cam->forward.x, eye.y + cam->forward.y, eye.z + cam->forward.z };

  gluLookAt(eye.x, eye.y, eye.z, center.x, center.y, center.z, cam->up.x, cam->up.y, cam->up.z);
}

void move_forward(Camera* cam) {
  const float speed = 0.1f;
  cam->position.x += cam->forward.x * speed;
  cam->position.y += cam->forward.y * speed;
  cam->position.z += cam->forward.z * speed;
}

void move_backward(Camera* cam) {
  const float speed = 0.1f;
  cam->position.x -= cam->forward.x * speed;
  cam->position.y -= cam->forward.y * speed;
  cam->position.z -= cam->forward.z * speed;
}

void move_right(Camera* cam) {
  const float speed = 0.1f;

  Vec3 movementDirection = crossProduct((Vec3) { cam->forward.x, cam->forward.y, cam->forward.z }, (Vec3) { 0.0f, 1.0f, 0.0f });

  cam->position.x += movementDirection.x * speed;
  cam->position.y += movementDirection.y * speed;
  cam->position.z += movementDirection.z * speed;
}

void move_left(Camera* cam) {
  const float speed = 0.1f;

  Vec3 movementDirection = crossProduct((Vec3) { cam->forward.x, cam->forward.y, cam->forward.z }, (Vec3) { 0.0f, 1.0f, 0.0f });
  cam->position.x -= movementDirection.x * speed;
  cam->position.y -= movementDirection.y * speed;
  cam->position.z -= movementDirection.z * speed;
}

Vec3 crossProduct(Vec3 a, Vec3 b) {
  Vec3 c;
  c.x = a.y * b.z - a.z * b.y;
  c.y = a.z * b.x - a.x * b.z;
  c.z = a.x * b.y - a.y * b.x;

  return c;
}