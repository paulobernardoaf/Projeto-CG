#include <math.h>
#include <ctype.h>

#include <GL/gl.h>
#include <GL/freeglut.h>

#include "libs/vector.h"
#include "libs/colors.h"
#include "libs/camera/camera.h"
#include "libs/draws/draw.h"

#define WINDOW_WIDTH 16*75
#define WINDOW_HEIGHT 9*75
// Global variables

Vec2 WINDOW_SIZE = { WINDOW_WIDTH, WINDOW_HEIGHT };
Vec2 WINDOW_CENTER = { WINDOW_WIDTH/2, WINDOW_HEIGHT / 2 };
float FOVY = 60.0f;
float ZNEAR = 10e-3;
Camera CAM;
int KEYBOARD[128] = { 0 };

void init_gl();

// Callbacks

void display();

void idle();

void motion(int x, int y);

void keyboard(unsigned char key, int x, int y);

void keyboard_up(unsigned char key, int x, int y);

void reshape(int width, int height);


// Drawing utils

void draw_axis(int x, int y, int z);

void draw_grid(int n);


int main(int argc, char** argv) {
  glutInit(&argc, argv);

  glutInitWindowSize(WINDOW_SIZE.x, WINDOW_SIZE.y);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutCreateWindow("Projeto CG");
  glutWarpPointer(WINDOW_CENTER.x, WINDOW_CENTER.y);

  glutDisplayFunc(display);
  glutIdleFunc(idle);
  glutPassiveMotionFunc(motion);
  glutKeyboardFunc(keyboard);
  glutKeyboardUpFunc(keyboard_up);
  glutReshapeFunc(reshape);

  init_gl();

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
  
  draw_grid(20);
  draw_axis(1, 1, 1);
  Object kitchen = (Object){ 9.0f, 5.0f, 15.0f };
  buildKitchen(kitchen);

  glutSwapBuffers();
}

void idle() {
  // Forward movement
  int move_forward = KEYBOARD['w'] - KEYBOARD['s'];
  Vec3 fwd = forward(&CAM);

  fwd.x *= move_forward;
  fwd.y = 0.0f; // Projects fwd in the xz plane
  fwd.z *= move_forward;

  // Lateral movement
  int move_right = KEYBOARD['d'] - KEYBOARD['a'];
  Vec3 rgt = right(&CAM);

  rgt.x *= move_right;
  rgt.z *= move_right;

  CAM.position.x += 0.1f * (fwd.x + rgt.x);
  CAM.position.z += 0.1f * (fwd.z + rgt.z);

  glutPostRedisplay();
}

void motion(int x, int y) {
  static int wrap = 0;
  Vec2 delta;

  if (!wrap) {
    delta.x = x - WINDOW_CENTER.x;
    delta.y = y - WINDOW_CENTER.y;

    CAM.rotation.x += delta.y > 0 ? -1.0f : (delta.y < 0 ? 1.0f : 0.0f);
    CAM.rotation.y -= delta.x > 0 ? 1.0f : (delta.x < 0 ? -1.0f : 0.0f);

    wrap = 1;
    glutWarpPointer(WINDOW_CENTER.x, WINDOW_CENTER.y);
  }
  else {
    wrap = 0;
  }
}

void keyboard(unsigned char key, int x, int y) {
  if (key == 27)
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
