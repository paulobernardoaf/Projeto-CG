#include <math.h>
#include <ctype.h>
#include <stdio.h>

#include <GL/gl.h>
#include <GL/freeglut.h>

#include "libs/vector.h"
#include "libs/colors.h"
#include "libs/camera/camera.h"
#include "libs/draws/draw.h"
#include "libs/animations/animation.h"
#include "libs/loader/loader.h"

#define WINDOW_WIDTH 16*75
#define WINDOW_HEIGHT 9*75
// Global variables

const float DEG2RAD = M_PI / 180.0f;
float speed = 0.1f;
Vec2 WINDOW_SIZE = { WINDOW_WIDTH, WINDOW_HEIGHT };
Vec2 WINDOW_CENTER = { WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 };
float FOVY = 60.0f;
float ZNEAR = 10e-3;
Camera CAM;
int KEYBOARD[128] = { 0 };

int DOOR_STEP = 3;
float DOOR_ANGLE = 0.0f;

int WINDOW_STEP = 1;
float WINDOW_ANGLE = -45.0f;

// Objects
Object3d fridge;
Object3d microwave;
Object3d stove;
Object3d tap;
Object3d chair;

void init_gl();

void display();

void motion(int x, int y);

void keyboard(unsigned char key, int x, int y);

void keyboard_up(unsigned char key, int x, int y);

void reshape(int width, int height);

void update(int value) {

  float MOVEMENT_SPEED = 2.0f;

  Vec3 forward = (Vec3){ 0.0f, 0.0f, 0.0f };
  Vec3 backwards;

  if (KEYBOARD['w']) {
    move_forward(&CAM);
  }

  if (KEYBOARD['s']) {
    move_backward(&CAM);
  }

  if (KEYBOARD['d']) {
    move_right(&CAM);
  }

  if (KEYBOARD['a']) {
    move_left(&CAM);
  }

  glutPostRedisplay();
  glutTimerFunc(15, update, 0);
}

int initializeObjects() {

  fridge = load_obj("./objs/fridge/Fridge.obj", 4);
  if (!fridge.VERTEX_COUNT) {
    printf("Erro opening fridge .obj file!");
    return 0;
  }

  microwave = load_obj("./objs/microwave/Microwave.obj", 4);
  if (!microwave.VERTEX_COUNT) {
    printf("Erro opening microwave .obj file!");
    return 0;
  }

  stove = load_obj("./objs/stove/Stove.obj", 4);
  if (!stove.VERTEX_COUNT) {
    printf("Erro opening stove .obj file!");
    return 0;
  }

  tap = load_obj("./objs/tap/tap.obj", 4);
  if (!tap.VERTEX_COUNT) {
    printf("Erro opening stove .obj file!");
    return 0;
  }

  chair = load_obj("./objs/chair/chair.obj", 4);
  if (!chair.VERTEX_COUNT) {
    printf("Erro opening stove .obj file!");
    return 0;
  }

  return 1;
}

int main(int argc, char** argv) {
  glutInit(&argc, argv);

  glutInitWindowSize(WINDOW_SIZE.x, WINDOW_SIZE.y);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutCreateWindow("Projeto CG");
  glutWarpPointer(WINDOW_CENTER.x, WINDOW_CENTER.y);

  glutDisplayFunc(display);
  glutPassiveMotionFunc(motion);
  glutKeyboardFunc(keyboard);
  glutKeyboardUpFunc(keyboard_up);
  glutReshapeFunc(reshape);
  glutTimerFunc(15, update, 0);

  init_gl();

  if (!initializeObjects()) {
    printf("Failing");
    return -1;
  };

  initializeCamera(&CAM);

  glutMainLoop();

  return 0;
}


void init_gl() {
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
}

// Callbacks
void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(0.31, 0.61, 0.85, 1.0);

  setupCamera(&CAM);

  Object kitchen = (Object){ 9.0f, 5.0f, 15.0f };
  buildKitchen(kitchen);

  buildFridge(fridge, 4);
  buildMicrowave(microwave, 4);
  buildStove(stove, 4);
  buildTap(tap, 4);
  buildChair(chair, 4);

  buildCabinet(kitchen);
  buildTable();

  handleDoorAnimation();
  buildDoor(kitchen, DOOR_ANGLE);

  handleWindowAnimation();
  buildWindow(kitchen, WINDOW_ANGLE);

  glutSwapBuffers();
}

void normalizeVector(Vec3* vec) {
  float magnitude = sqrt((vec->x * vec->x) + (vec->y * vec->y) + (vec->z * vec->z));

  vec->x = vec->x / magnitude;
  vec->y = vec->y / magnitude;
  vec->z = vec->z / magnitude;
}

void motion(int x, int y) {
  Vec2 delta;
  float speed = 0.8f;

  delta.x = (x - WINDOW_CENTER.x) * speed;
  delta.y = (y - WINDOW_CENTER.y) * speed;

  if (delta.y > 89.0f) {
    delta.y = 89.0f;
  }
  if (delta.y < -89.0f) {
    delta.y = -89.0f;
  }

  CAM.forward.x = cos(delta.x * DEG2RAD) * cos(delta.y * DEG2RAD);
  CAM.forward.y = sin(-delta.y * DEG2RAD);
  CAM.forward.z = sin(delta.x * DEG2RAD) * cos(delta.y * DEG2RAD);

  normalizeVector(&CAM.forward);
}

void keyboard(unsigned char key, int x, int y) {
  if (key == '1') {
    handleDoor();
  }
  else if (key == '2') {
    handleWindow();
  }
  else if (key == 27)
    glutLeaveMainLoop();

  KEYBOARD[tolower(key)] = 1;
}

void keyboard_up(unsigned char key, int x, int y) {
  KEYBOARD[tolower(key)] = 0;
}

void reshape(int width, int height) {
  float aspect = (float)width / (float)height;
  WINDOW_SIZE.x = width;
  WINDOW_SIZE.y = height;
  WINDOW_CENTER.x = width / 2;
  WINDOW_CENTER.y = height / 2;

  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(FOVY, aspect, ZNEAR, ZFAR);
}
