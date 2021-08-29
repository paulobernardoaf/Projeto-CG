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

void buildFace(Vec3 vertices[], Vec3 origin, Color color) {

  glBegin(GL_QUADS);
  glColor3f(color.red / 255, color.green / 255, color.blue / 255);

  for (int i = 0; i < 4; i++) {
    glVertex3f(origin.x + vertices[i].x, origin.y + vertices[i].y, origin.z + vertices[i].z);
  }

  glEnd();

}

void buildBlock(Object block, Vec3 origin, Color color) {

  glPushMatrix();
  Vec3 vertices[4];
  float width = block.width;
  float height = block.height;
  float depth = block.depth;

  // Bottom
  vertices[0] = (Vec3){ 0.0f, 0.0f, 0.0f };
  vertices[1] = (Vec3){ width, 0.0f, 0.0f };
  vertices[2] = (Vec3){ width, 0.0f, depth };
  vertices[3] = (Vec3){ 0.0f, 0.0f, depth };
  buildFace(vertices, origin, color);

  // Top
  vertices[0] = (Vec3){ 0.0f, height, 0.0f };
  vertices[1] = (Vec3){ 0.0f, height, depth };
  vertices[2] = (Vec3){ width, height, depth };
  vertices[3] = (Vec3){ width, height, 0.0f };
  buildFace(vertices, origin, color);

  // Front
  vertices[0] = (Vec3){ 0.0f, 0.0f, 0.0f };
  vertices[1] = (Vec3){ 0.0f, height, 0.0f };
  vertices[2] = (Vec3){ width, height, 0.0f };
  vertices[3] = (Vec3){ width, 0.0f, 0.0f };
  buildFace(vertices, origin, color);

  // Back
  vertices[0] = (Vec3){ 0.0f, 0.0f, depth };
  vertices[1] = (Vec3){ width, 0.0f, depth };
  vertices[2] = (Vec3){ width, height, depth };
  vertices[3] = (Vec3){ 0.0f, height, depth };
  buildFace(vertices, origin, color);

  // Left
  vertices[0] = (Vec3){ width, 0.0f, depth };
  vertices[1] = (Vec3){ width, 0.0f, 0.0f };
  vertices[2] = (Vec3){ width, height, 0.0f };
  vertices[3] = (Vec3){ width, height, depth };
  buildFace(vertices, origin, color);

  // Right
  vertices[0] = (Vec3){ 0.0f, 0.0f, 0.0f };
  vertices[1] = (Vec3){ 0.0f, 0.0f, depth };
  vertices[2] = (Vec3){ 0.0f, height, depth };
  vertices[3] = (Vec3){ 0.0f, height, 0.0f };
  buildFace(vertices, origin, color);
  glPopMatrix();
};

void buildBackWall(Object wall, Vec3 origin, Color color) {

  Vec3 position;

  // right
  Object right = (Object){ wall.width / 3, wall.height, wall.depth };
  position = (Vec3){ origin.x, origin.y, origin.z };
  buildBlock(right, position, color);

  // top
  Object top = (Object){ wall.width / 3, wall.height / 3, wall.depth };
  position = (Vec3){ origin.x + (wall.width / 3), origin.y + 2 * wall.height / 3, origin.z };
  buildBlock(top, position, color);

  // bottom
  Object bottom = (Object){ wall.width / 3, wall.height / 3, wall.depth };
  position = (Vec3){ origin.x + wall.width / 3, origin.y, origin.z };
  buildBlock(bottom, position, color);

  // left
  Object left = (Object){ wall.width / 3, wall.height, wall.depth };
  position = (Vec3){ origin.x + 2 * wall.width / 3, origin.y, origin.z };
  buildBlock(left, position, color);

}

void buildLeftWall(Object wall, Vec3 origin, Color color) {

  Vec3 position;

  // top
  color = (Color){ 110.0f, 0.0f, 149.0f };
  Object top = (Object){ wall.width, wall.height / 4, wall.depth / 6 };
  position = (Vec3){ origin.x, origin.y + 3 * wall.height / 4, origin.z + 5 * wall.depth / 6 };
  buildBlock(top, position, color);

  // left
  color = (Color){ 113.0f, 111.0f, 129.0f };
  Object left = (Object){ wall.width, wall.height, 5 * wall.depth / 6 };
  position = (Vec3){ origin.x, origin.y, origin.z };
  buildBlock(left, position, color);
}

void buildKitchen(Object kitchen) {

  Color color;
  Object wall;
  Vec3 origin;

  float wallDepth = 0.25f;

  // floor
  color = (Color){ 113.0f, 111.0f, 129.0f };
  wall = (Object){ kitchen.width, 0.0f, kitchen.depth };
  origin = (Vec3){ 0.0f, 0.0f, 0.0f };
  buildBlock(wall, origin, color);

  // ceil
  color = (Color){ 255.0f, 0.0f, 149.0f };
  wall = (Object){ kitchen.width, 0.0f, kitchen.depth };
  origin = (Vec3){ 0.0f, kitchen.height, 0.0f };
  buildBlock(wall, origin, color);

  // front wall
  color = (Color){ 243.0f, 139.0f, 160.0f };
  wall = (Object){ kitchen.width, kitchen.height, 0.0f };
  origin = (Vec3){ 0.0f, 0.0f, 0.0f };
  buildBlock(wall, origin, color);

  // back wall
  color = (Color){ 246.0f, 174.0f, 153.0f };
  wall = (Object){ kitchen.width, kitchen.height, wallDepth };
  origin = (Vec3){ 0.0f, 0.0f, kitchen.depth };
  buildBackWall(wall, origin, color);

  // right wall
  color = (Color){ 242.0f, 225.0f, 193.0f };
  wall = (Object){ 0.0f, kitchen.height, kitchen.depth };
  origin = (Vec3){ 0.0f, 0.0f, 0.0f };
  buildBlock(wall, origin, color);

  // left wall
  color = (Color){ 255.0f, 0.0f, 0.0f };
  wall = (Object){ wallDepth, kitchen.height, kitchen.depth };
  origin = (Vec3){ kitchen.width, 0.0f, 0.0f };
  buildLeftWall(wall, origin, color);
}

void buildDoor(Object kitchen, float doorAngle) {
  
  Color color;
  Object wall;
  Vec3 origin;

  float doorDepth = 0.125f;

  glPushMatrix();
  color = (Color){ 240.0f, 240.0f, 240.0f };
  wall = (Object){ doorDepth, 3 * kitchen.height / 4, kitchen.depth / 6 - doorDepth};
  origin = (Vec3){ 0.0f, 0.0f, 0.0f };
  glTranslatef(kitchen.width + doorDepth, 0.0f, kitchen.depth - doorDepth);
  glRotatef(180.0f + doorAngle, 0.0f, 1.0f, 0.0f);
  buildBlock(wall, origin, color);

  glPopMatrix();
}