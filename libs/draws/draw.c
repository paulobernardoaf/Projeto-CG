#include "draw.h"
#include "../colors.h"
#include "../vector.h"
#include "../loader/loader.h"

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

void draw_grid(int n, int m) {

  int i;

  glBegin(GL_LINES);
  glColor3f(WHITE);
  for (i = 0;i <= n;i++) {
    float d = (float)i;
    // Parallel to x-axis 
    glVertex3f(0, 0.01f, d);
    glVertex3f(m, 0.01f, d);
  }
  for (i = 0;i <= m;i++) {
    float d = (float)i;
    // Parallel to z-axis
    glVertex3f(d, 0.01f, 0);
    glVertex3f(d, 0.01f, n);
  }
  glEnd();

}

void buildFace(Vec3 vertices[], Color color) {

  glBegin(GL_QUADS);
  glColor3f(color.red / 255, color.green / 255, color.blue / 255);

  for (int i = 0; i < 4; i++) {
    glVertex3f(vertices[i].x, vertices[i].y, vertices[i].z);
  }

  glEnd();

}

void buildBlock(Object block, Color color) {

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
  buildFace(vertices, color);

  // Top
  vertices[0] = (Vec3){ 0.0f, height, 0.0f };
  vertices[1] = (Vec3){ 0.0f, height, depth };
  vertices[2] = (Vec3){ width, height, depth };
  vertices[3] = (Vec3){ width, height, 0.0f };
  buildFace(vertices, color);

  // Front
  vertices[0] = (Vec3){ 0.0f, 0.0f, 0.0f };
  vertices[1] = (Vec3){ 0.0f, height, 0.0f };
  vertices[2] = (Vec3){ width, height, 0.0f };
  vertices[3] = (Vec3){ width, 0.0f, 0.0f };
  buildFace(vertices, color);

  // Back
  vertices[0] = (Vec3){ 0.0f, 0.0f, depth };
  vertices[1] = (Vec3){ width, 0.0f, depth };
  vertices[2] = (Vec3){ width, height, depth };
  vertices[3] = (Vec3){ 0.0f, height, depth };
  buildFace(vertices, color);

  // Left
  vertices[0] = (Vec3){ width, 0.0f, depth };
  vertices[1] = (Vec3){ width, 0.0f, 0.0f };
  vertices[2] = (Vec3){ width, height, 0.0f };
  vertices[3] = (Vec3){ width, height, depth };
  buildFace(vertices, color);

  // Right
  vertices[0] = (Vec3){ 0.0f, 0.0f, 0.0f };
  vertices[1] = (Vec3){ 0.0f, 0.0f, depth };
  vertices[2] = (Vec3){ 0.0f, height, depth };
  vertices[3] = (Vec3){ 0.0f, height, 0.0f };
  buildFace(vertices, color);
  glPopMatrix();
};

void buildBackWall(Object wall, Color color) {

  // right
  glPushMatrix(); {
    Object right = (Object){ wall.width / 3, wall.height, wall.depth };
    buildBlock(right, color);
  } glPopMatrix();

  // top
  glPushMatrix(); {
    Object top = (Object){ wall.width / 3, wall.height / 3, wall.depth };
    glTranslatef(wall.width / 3, 2 * wall.height / 3, 0.0f);
    buildBlock(top, color);
  } glPopMatrix();

  // bottom
  glPushMatrix(); {
    Object bottom = (Object){ wall.width / 3, wall.height / 3, wall.depth };
    glTranslatef(wall.width / 3, 0.0f, 0.0f);
    buildBlock(bottom, color);
  } glPopMatrix();

  // left
  glPushMatrix(); {
    Object left = (Object){ wall.width / 3, wall.height, wall.depth };
    glTranslatef(2 * wall.width / 3, 0.0f, 0.0f);
    buildBlock(left, color);
  } glPopMatrix();

}

void buildLeftWall(Object wall, Color color) {

  Vec3 position;

  // top
  glPushMatrix(); {
    color = (Color){ 110.0f, 0.0f, 149.0f };
    Object top = (Object){ wall.width, wall.height / 4, wall.depth / 6 };
    glTranslatef(0.0f, 3 * wall.height / 4, 5 * wall.depth / 6);
    buildBlock(top, color);
  } glPopMatrix();

  // left
  glPushMatrix(); {
    color = (Color){ 113.0f, 111.0f, 129.0f };
    Object left = (Object){ wall.width, wall.height, 5 * wall.depth / 6 };
    buildBlock(left, color);
  } glPopMatrix();
}

void buildKitchen(Object kitchen) {

  Color color;
  Object wall;
  Vec3 origin;

  float wallDepth = 0.25f;

  // floor
  glPushMatrix(); {
    color = (Color){ 113.0f, 111.0f, 129.0f };
    wall = (Object){ kitchen.width, 0.0f, kitchen.depth };
    // origin = (Vec3){ 0.0f, 0.0f, 0.0f };
    buildBlock(wall, color);
  } glPopMatrix();
  glPushMatrix(); {

    // ceil
    color = (Color){ 255.0f, 0.0f, 149.0f };
    wall = (Object){ kitchen.width, 0.0f, kitchen.depth };
    // origin = (Vec3){ 0.0f, kitchen.height, 0.0f };
    glTranslatef(0.0f, kitchen.height, 0.0f);
    buildBlock(wall, color);
  } glPopMatrix();

  // front wall
  glPushMatrix(); {
    color = (Color){ 243.0f, 139.0f, 160.0f };
    wall = (Object){ kitchen.width, kitchen.height, 0.0f };
    // origin = (Vec3){ 0.0f, 0.0f, 0.0f };
    buildBlock(wall, color);
  } glPopMatrix();

  // back wall
  glPushMatrix(); {
    color = (Color){ 246.0f, 174.0f, 153.0f };
    wall = (Object){ kitchen.width, kitchen.height, wallDepth };
    // origin = (Vec3){ 0.0f, 0.0f, kitchen.depth };
    glTranslatef(0.0f, 0.0f, kitchen.depth);
    buildBackWall(wall, color);
  } glPopMatrix();

  // right wall
  glPushMatrix(); {
    color = (Color){ 242.0f, 225.0f, 193.0f };
    wall = (Object){ 0.0f, kitchen.height, kitchen.depth };
    // origin = (Vec3){ 0.0f, 0.0f, 0.0f };
    buildBlock(wall, color);
  } glPopMatrix();

  // left wall
  glPushMatrix(); {
    color = (Color){ 255.0f, 0.0f, 0.0f };
    wall = (Object){ wallDepth, kitchen.height, kitchen.depth };
    // origin = (Vec3){ kitchen.width, 0.0f, 0.0f };
    glTranslatef(kitchen.width, 0.0f, 0.0f);
    buildLeftWall(wall, color);
  } glPopMatrix();
}

void buildDoor(Object kitchen, float doorAngle) {

  Color color;
  Object wall;
  Vec3 origin;

  float doorDepth = 0.125f;

  glPushMatrix();
  color = (Color){ 240.0f, 240.0f, 240.0f };
  wall = (Object){ doorDepth, 3 * kitchen.height / 4, kitchen.depth / 6 - doorDepth };
  glTranslatef(kitchen.width + doorDepth, 0.0f, kitchen.depth - doorDepth);
  glRotatef(180.0f + doorAngle, 0.0f, 1.0f, 0.0f);
  buildBlock(wall, color);

  glPopMatrix();
}

void buildWindow(Object kitchen, float windowAngle) {

  float glassDepth = 0.05f;
  float rotationOffset = 0.25f;

  Color color = (Color){ 148.0f, 201.0f, 228.0f };
  Object window = (Object){ kitchen.width / 3, (kitchen.height / 3) / 4, glassDepth };

  glPushMatrix(); {
    glPushMatrix(); {
      glTranslatef(window.width, (kitchen.height / 3), kitchen.depth + 0.25f / 2 - glassDepth / 2);
      buildBlock(window, color);
    } glPopMatrix();

    glPushMatrix(); {
      glTranslatef(window.width, (kitchen.height / 3) + window.height + rotationOffset, kitchen.depth + 0.25f / 2 - glassDepth / 2);
      glPushMatrix(); {
        glRotatef(windowAngle, 1.0f, 0.0f, 0.0f);
        glTranslatef(0.0f, -rotationOffset, 0.0f);
        buildBlock(window, color);
      } glPopMatrix();
    } glPopMatrix();

    glPushMatrix(); {
      glTranslatef(window.width, (kitchen.height / 3) + (window.height * 2) + rotationOffset, kitchen.depth + 0.25f / 2 - glassDepth / 2);
      glPushMatrix(); {
        glRotatef(windowAngle, 1.0f, 0.0f, 0.0f);
        glTranslatef(0.0f, -rotationOffset, 0.0f);
        buildBlock(window, color);
      } glPopMatrix();
    } glPopMatrix();

    glPushMatrix(); {
      glTranslatef(window.width, (kitchen.height / 3) + (window.height * 3) + rotationOffset, kitchen.depth + 0.25f / 2 - glassDepth / 2);
      glPushMatrix(); {
        glRotatef(windowAngle, 1.0f, 0.0f, 0.0f);
        glTranslatef(0.0f, -rotationOffset, 0.0f);
        buildBlock(window, color);
      } glPopMatrix();
    } glPopMatrix();
  } glPopMatrix();
}

void buildObject(Object3d object, int faces) {
  glBegin(GL_LINES); // TODO: CHANGE BACK TO POLYGON
  for (int i = 0;i < object.VERTEX_COUNT;i++) {
    glNormal3f(object.NORMALS[i].x, object.NORMALS[i].y, object.NORMALS[i].z);
    glTexCoord2f(object.TEX_COORDS[i].x, object.TEX_COORDS[i].y);
    glVertex3f(object.VERTICES[i].x, object.VERTICES[i].y, object.VERTICES[i].z);
  }
  glEnd();
}

void buildFridge(Object3d fridge, int faces) {
  glPushMatrix(); {
    glTranslatef(1.0f, 0.0f, 14.0f);
    glScalef(0.018f, 0.018f, 0.018f);
    glRotatef(130.0f, 0.0f, 1.0f, 0.0f);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    glColor3f(0.0f / 255, 50.0f / 255, 50.0f / 255);
    buildObject(fridge, faces);
  } glPopMatrix();
}

void buildMicrowave(Object3d microwave, int faces) {
  glPushMatrix(); {

    glTranslatef(0.0f, 0.0f, 2.0f);

    // support
    glPushMatrix(); {
      Object section = (Object){ 1.25f, 0.1f, 1.2f };
      glTranslatef(0.001f, 1.9f, 7.4f);
      Color color = (Color){ 255.0f, 50.0f, 50.0f };
      buildBlock(section, color);
    } glPopMatrix();

    glPushMatrix(); {
      glTranslatef(0.7f, 2.0f, 8.0f);
      glScalef(0.02f, 0.02f, 0.02f);
      glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
      glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
      glColor3f(100.0f / 255, 50.0f / 255, 50.0f / 255);
      buildObject(microwave, faces);
    } glPopMatrix();
  } glPopMatrix();
}

void buildStove(Object3d stove, int faces) {
  glPushMatrix(); {
    glTranslatef(0.7f, 0.0f, 7.0f);
    glScalef(0.04f, 0.04f, 0.04f);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    glColor3f(0.0f / 255, 50.0f / 255, 50.0f / 255);
    buildObject(stove, faces);
  } glPopMatrix();
}

void buildTap(Object3d tap, int faces) {
  glPushMatrix(); {
    glTranslatef(0.71f, -0.3f, 8.25f);
    glScalef(0.002f, 0.002f, 0.002f);
    glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
    glColor3f(0.0f / 255, 50.0f / 255, 50.0f / 255);
    buildObject(tap, faces);
  } glPopMatrix();
}

void buildChair(Object3d chair, int faces) {
  glPushMatrix(); {
    glPushMatrix(); {
      glTranslatef(2.0f, 1.0f, 1.0f);
      glScalef(0.4f, 0.4f, 0.4f);
      // glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
      glColor3f(0.0f / 255, 50.0f / 255, 50.0f / 255);
      buildObject(chair, faces);
    } glPopMatrix();

    glPushMatrix(); {
      glTranslatef(3.5f, 1.0f, 2.0f);
      glScalef(0.4f, 0.4f, 0.4f);
      glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
      glColor3f(0.0f / 255, 50.0f / 255, 50.0f / 255);
      buildObject(chair, faces);
    } glPopMatrix();

    glPushMatrix(); {
      glTranslatef(5.5f, 1.0f, 2.0f);
      glScalef(0.4f, 0.4f, 0.4f);
      glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
      glColor3f(0.0f / 255, 50.0f / 255, 50.0f / 255);
      buildObject(chair, faces);
    } glPopMatrix();

    glPushMatrix(); {
      glTranslatef(8.0f, 1.0f, 1.0f);
      glScalef(0.4f, 0.4f, 0.4f);
      glRotatef(200.0f, 0.0f, 1.0f, 0.0f);
      glColor3f(0.0f / 255, 50.0f / 255, 50.0f / 255);
      buildObject(chair, faces);
    } glPopMatrix();
  } glPopMatrix();
}

void buildCabinet(Object kitchen) {
  glPushMatrix(); {

    Color color;
    Object section;

    // bottom section
    glPushMatrix(); {
      color = (Color){ 240.0f, 240.0f, 240.0f };
      section = (Object){ 1.25f, 1.5f, 3.0f };
      glTranslatef(kitchen.width - 1.25f, 0.0f, 5.0f);
      buildBlock(section, color);

      section = (Object){ 0.25f, 1.5f, 1.0f };
      glTranslatef(0.0f, 0.0f, 3.0f);
      buildBlock(section, color);

      section = (Object){ 1.25f, 1.5f, 3.0f };
      glTranslatef(0.0f, 0.0f, 1.0f);
      buildBlock(section, color);
    } glPopMatrix();

    // top section
    glPushMatrix(); {
      color = (Color){ 240.0f, 240.0f, 240.0f };
      section = (Object){ 1.25f, 1.5f, 7.0f };
      glTranslatef(kitchen.width - 1.25f, 3.0f, 5.0f);
      buildBlock(section, color);
    } glPopMatrix();

    // sink
    glPushMatrix(); {

      glTranslatef(kitchen.width - 1.0f, 1.3f, 8.0f);
      //bottom
      glPushMatrix(); {
        color = (Color){ 0.0f, 140.0f, 240.0f };
        section = (Object){ 1.0f, 0.1f, 1.0f };
        // glTranslatef(2.0f, 1.5f, 4.0f);
        buildBlock(section, color);
      } glPopMatrix();

      // left
      glPushMatrix(); {
        color = (Color){ 0.0f, 240.0f, 240.0f };
        section = (Object){ 1.0f, 0.2f, 0.1f };
        glTranslatef(0.0f, 0.1f, 0.0f);
        // glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
        buildBlock(section, color);
      } glPopMatrix();

      // right
      glPushMatrix(); {
        color = (Color){ 0.0f, 240.0f, 240.0f };
        section = (Object){ 1.0f, 0.2f, 0.1f };
        glTranslatef(0.0f, 0.1f, 0.9f);
        // glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
        buildBlock(section, color);
      } glPopMatrix();

      // front
      glPushMatrix(); {
        color = (Color){ 0.0f, 240.0f, 240.0f };
        section = (Object){ 0.1f, 0.2f, 1.0f };
        glTranslatef(0.0f, 0.1f, 0.0f);
        // glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
        buildBlock(section, color);
      } glPopMatrix();

      // back
      glPushMatrix(); {
        color = (Color){ 0.0f, 240.0f, 240.0f };
        section = (Object){ 0.1f, 0.2f, 1.0f };
        glTranslatef(0.9f, 0.1f, 0.0f);
        // glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
        buildBlock(section, color);
      } glPopMatrix();

      // hole
      glPushMatrix(); {
        color = (Color){ 0.0f, 0.0f, 0.0f };
        section = (Object){ 0.1f, 0.1f, 0.1f };
        glTranslatef(0.5f, 0.001f, 0.45f);
        // glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
        buildBlock(section, color);
      } glPopMatrix();
    } glPopMatrix();

  } glPopMatrix();
}

void buildTable() {
  glPushMatrix(); {
    Object section;
    Object topSection;
    Color color = (Color){ 80.0f, 60.0f, 0.0f };

    // board
    glPushMatrix(); {
      section = (Object){ 5.0f, 0.1f, 2.0f };
      glTranslatef(2.0f, 1.5f, 0.0f);
      buildBlock(section, color);
    } glPopMatrix();

    //legs
    glPushMatrix(); {
      glTranslatef(2.0f, 0.0f, 0.0f);
      glPushMatrix(); {
        section = (Object){ 0.1f, 1.5f, 0.1f };
        buildBlock(section, color);
      } glPopMatrix();

      glPushMatrix(); {
        section = (Object){ 0.1f, 1.5f, 0.1f };
        glTranslatef(0.0f, 0.0f, 1.9f);
        buildBlock(section, color);
      } glPopMatrix();

      glPushMatrix(); {
        section = (Object){ 0.1f, 1.5f, 0.1f };
        glTranslatef(4.9f, 0.0f, 1.9f);
        buildBlock(section, color);
      } glPopMatrix();

      glPushMatrix(); {
        section = (Object){ 0.1f, 1.5f, 0.1f };
        glTranslatef(4.9f, 0.0f, 0.0f);
        buildBlock(section, color);
      } glPopMatrix();


    }

  } glPopMatrix();
}