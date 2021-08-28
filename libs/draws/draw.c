#include "draw.h"
#include "../colors.h"
#include "../vector.h"

#include <math.h>
#include <ctype.h>

#include <GL/gl.h>
#include <GL/freeglut.h>

void draw_axis(int x, int y, int z) {
  glLineWidth(3.0f);
  glBegin(GL_LINES);
  if (x) {
    glColor3f(RED);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(ZFAR, 0.0f, 0.0f);
  }
  if (y) {
    glColor3f(GREEN);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, ZFAR, 0.0f);
  }
  if (z) {
    glColor3f(BLUE);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, ZFAR);
  }
  glEnd();
  glLineWidth(1.0f);
}

void draw_grid(int n) {
  int i;

  glBegin(GL_LINES);
  glColor3f(WHITE);
  for (i = -n;i < n;i++) {
    float d = (float)i;
    // Parallel to x-axis 
    glVertex3f(-n, 0.0f, d);
    glVertex3f(n, 0.0f, d);
    // Parallel to z-axis
    glVertex3f(d, 0.0f, -n);
    glVertex3f(d, 0.0f, n);
  }
  glEnd();
}

void buildWall(Vec3 position, Object scale, Rotation rotation, Color color) {
  glPushMatrix();
  glColor3f(color.red / 255, color.green / 255, color.blue / 255);
  glTranslatef(position.x, position.y, position.z);
  glRotatef(rotation.degrees, rotation.axis.x, rotation.axis.y, rotation.axis.z);
  glScalef(scale.width, scale.height, scale.depth);

  /*
  Desenha o cubo de lado 1 com todas as transformacoes acima
  aplicadas.
  A origem do cubo eh no centro, entao lembre de colocar
  altura/2 na coordenada y da posicao para ficar
  perfeitamente no chao
  */
  glutSolidCube(1.0f);
  glPopMatrix();
}

void drawRoom() {

  Vec3 position;
  Object scale;
  Rotation rotation;
  Color color;

  // Floor
  scale = (Object){ 10.0f, 20.0f, 0.5f };
  position = (Vec3){ scale.width / 2, -scale.depth / 2, scale.height / 2 };
  rotation = (Rotation){ 90.0f, (Vec3) { 1.0f, 0.0f, 0.0f } };
  color = (Color){ 113.0f, 111.0f, 129.0f };
  buildWall(position, scale, rotation, color);

  // Front wall
  scale = (Object){ 20.0f, 5.0f, 0.5f };
  position = (Vec3){ scale.width / 2, scale.height / 2, scale.width / 2 };
  rotation = (Rotation){ 90.0f, (Vec3) { 0.0f, 1.0f, 0.0f } };
  color = (Color){ 185.0f, 122.0f, 149.0f };
  buildWall(position, scale, rotation, color);

  // Back wall
  scale = (Object){ 20.0f, 5.0f, 0.5f };
  position = (Vec3){ 0.0f, scale.height / 2, scale.width / 2 };
  rotation = (Rotation){ 90.0f, (Vec3) { 0.0f, 1.0f, 0.0f } };
  color = (Color){ 246.0f, 174.0f, 153.0f };
  buildWall(position, scale, rotation, color);

  // Left wall
  scale = (Object){ 10.0f, 5.0f, 0.5f };
  position = (Vec3){ scale.width / 2, scale.height / 2, 0.0f };
  rotation = (Rotation){ 0.0f, (Vec3) { 0.0f, 1.0f, 0.0f } };
  color = (Color){ 242.0f, 225.0f, 193.0f };
  buildWall(position, scale, rotation, color);

  // Right wall
  scale = (Object){ 10.0f, 5.0f, 0.5f };
  position = (Vec3){ scale.width / 2, scale.height / 2, scale.width*2 };
  rotation = (Rotation){ 0.0f, (Vec3) { 0.0f, 1.0f, 0.0f } };
  color = (Color){ 243.0f, 139.0f, 160.0f };
  buildWall(position, scale, rotation, color);
}
