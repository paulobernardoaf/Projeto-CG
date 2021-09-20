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

int enable = 1;

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

float FAN_ROTATION = 0.0f;

// Light Props

GLfloat light0_ambient[] = { 0.1, 0.1, 0.1, 1.0 };
GLfloat light0_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
GLfloat light0_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light0_position[] = { 4.5f, 4.5f, 9.0f, 1.0f };

float mat_shininess[] = { 50.0f };

// Objects
Object3d fridge;
Object3d microwave;
Object3d stove;
Object3d tap;
Object3d chair;
Object3d lamp;
Object3d fan;

// Textures
Texture microwaveTexture;
Texture fridgeTexture;
Texture stoveTexture;
Texture chairTexture;
Texture tableTexture;
Texture tapTexture;
Texture doorTexture;
Texture lampTexture;
Texture fanTexture;

void init_gl();

void setup_lighting();

void initLights();

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

  lamp = load_obj("./objs/lamp/lamp.obj", 4);
  if (!lamp.VERTEX_COUNT) {
    printf("Erro opening stove .obj file!");
    return 0;
  }

  fan = load_obj("./objs/fan/fan.obj", 4);
  if (!fan.VERTEX_COUNT) {
    printf("Erro opening stove .obj file!");
    return 0;
  }

  return 1;
}

void initializeTextures() {
  load_texture("./objs/microwave/microwave_texture.jpg", &microwaveTexture);
  setupTexture(&microwaveTexture);

  load_texture("./objs/fridge/fridge_texture.jpg", &fridgeTexture);
  setupTexture(&fridgeTexture);

  load_texture("./objs/stove/stove_texture.jpg", &stoveTexture);
  setupTexture(&stoveTexture);

  load_texture("./objs/chair/chair_texture.jpg", &chairTexture);
  setupTexture(&chairTexture);

  load_texture("./objs/chair/chair_texture.jpg", &tableTexture);
  setupTexture(&tableTexture);

  load_texture("./objs/fridge/fridge_texture.jpg", &tapTexture);
  setupTexture(&tapTexture);

  load_texture("./objs/door_texture.png", &doorTexture);
  setupTexture(&doorTexture);

  load_texture("./objs/lamp/lamp_texture.jpg", &lampTexture);
  setupTexture(&lampTexture);

  load_texture("./objs/fan/fan_texture.jpg", &fanTexture);
  setupTexture(&fanTexture);

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

  initializeCamera(&CAM);

  setup_lighting();

  glEnable(GL_COLOR_MATERIAL);
  glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

  initializeTextures();

  if (!initializeObjects()) {
    printf("Failing");
    return -1;
  };

  glutMainLoop();

  return 0;
}


void init_gl() {
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
}

void setup_lighting() {
  // glEnable(GL_LIGHTING);
  // glEnable(GL_LIGHT0);
  // glEnable(GL_DEPTH_TEST);

  glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

  // Anti aliasing smoothing props ........................................................
  glEnable(GL_LINE_SMOOTH);
  glEnable(GL_POINT_SMOOTH);
  glEnable(GL_BLEND);

  // Lighting and Shade setup .............................................................
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
  glShadeModel(GL_SMOOTH);
}

void initLights() {
  glPushMatrix(); {

    glEnable(GL_LIGHTING);

    glPushMatrix(); {
      glEnable(GL_LIGHT0);
      glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
      glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
      glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);
      glLightfv(GL_LIGHT0, GL_POSITION, light0_position);

    } glPopMatrix();
  } glPopMatrix();


}

// Callbacks
void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(0.31, 0.61, 0.85, 1.0);

  setupCamera(&CAM);

  initLights();

  Object kitchen = (Object){ 9.0f, 5.0f, 15.0f };
  buildKitchen(kitchen);

  buildFridge(fridge, 4, fridgeTexture);
  buildMicrowave(microwave, 4, microwaveTexture);
  buildStove(stove, 4, stoveTexture);
  buildTap(tap, 4, tapTexture);
  buildChair(chair, 4, chairTexture);
  buildLamp(lamp, 4, lampTexture);

  handleFanAnimation();
  buildFan(fan, 4, FAN_ROTATION, fanTexture);

  buildCabinet(kitchen);
  buildTable(tableTexture);

  handleDoorAnimation();
  buildDoor(kitchen, DOOR_ANGLE, doorTexture);

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
  else if (key == 27) {
    glutLeaveMainLoop();
  }
  else if (key == '3') {
    enable = !enable;
  }

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
