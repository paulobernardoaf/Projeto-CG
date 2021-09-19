#include "draw.h"
#include "../colors.h"
#include "../vector.h"
#include "../loader/loader.h"

#include <math.h>
#include <ctype.h>

#include <GL/gl.h>
#include <GL/freeglut.h>


void buildFace(Vec3 vertices[], Color color, Vec2 texCoord[]) {

  glBegin(GL_QUADS);
  glColor3f(color.red / 255, color.green / 255, color.blue / 255);

  for (int i = 0; i < 4; i++) {
    glTexCoord2f(texCoord[i].x, texCoord[i].y);
    glVertex3f(vertices[i].x, vertices[i].y, vertices[i].z);
  }

  glEnd();

}

void buildBlock(Object block, Color color) {

  glPushMatrix(); {
    GLfloat texCoordH = 1.0;
    GLfloat texCoordV = 1.0;

    Vec3 vertices[4];
    Vec2 texCoord[4];
    float width = block.width;
    float height = block.height;
    float depth = block.depth;

    // Bottom
    vertices[0] = (Vec3){ 0.0f, 0.0f, 0.0f };
    vertices[1] = (Vec3){ width, 0.0f, 0.0f };
    vertices[2] = (Vec3){ width, 0.0f, depth };
    vertices[3] = (Vec3){ 0.0f, 0.0f, depth };

    texCoord[0] = (Vec2){ 0.0, 0.0 };
    texCoord[1] = (Vec2){ 0.0, texCoordV };
    texCoord[2] = (Vec2){ texCoordH, texCoordV };
    texCoord[3] = (Vec2){ texCoordH, 0.0 };
    buildFace(vertices, color, texCoord);

    // Top
    vertices[0] = (Vec3){ 0.0f, height, 0.0f };
    vertices[1] = (Vec3){ 0.0f, height, depth };
    vertices[2] = (Vec3){ width, height, depth };
    vertices[3] = (Vec3){ width, height, 0.0f };

    texCoord[0] = (Vec2){ 0.0, 0.0 };
    texCoord[1] = (Vec2){ texCoordH, 0.0 };
    texCoord[2] = (Vec2){ texCoordH, texCoordV };
    texCoord[3] = (Vec2){ 0.0, texCoordV };
    buildFace(vertices, color, texCoord);

    // Front
    vertices[0] = (Vec3){ 0.0f, 0.0f, 0.0f };
    vertices[1] = (Vec3){ 0.0f, height, 0.0f };
    vertices[2] = (Vec3){ width, height, 0.0f };
    vertices[3] = (Vec3){ width, 0.0f, 0.0f };

    texCoord[0] = (Vec2){ 0.0, 0.0 };
    texCoord[1] = (Vec2){ 0.0, texCoordV };
    texCoord[2] = (Vec2){ texCoordH, texCoordV };
    texCoord[3] = (Vec2){ texCoordH, 0.0 };
    buildFace(vertices, color, texCoord);

    // Back
    vertices[0] = (Vec3){ 0.0f, 0.0f, depth };
    vertices[1] = (Vec3){ width, 0.0f, depth };
    vertices[2] = (Vec3){ width, height, depth };
    vertices[3] = (Vec3){ 0.0f, height, depth };

    texCoord[0] = (Vec2){ 0.0, 0.0 };
    texCoord[1] = (Vec2){ texCoordH, 0.0 };
    texCoord[2] = (Vec2){ texCoordH, texCoordV };
    texCoord[3] = (Vec2){ 0.0, texCoordV };
    buildFace(vertices, color, texCoord);

    // Left
    vertices[0] = (Vec3){ width, 0.0f, depth };
    vertices[1] = (Vec3){ width, 0.0f, 0.0f };
    vertices[2] = (Vec3){ width, height, 0.0f };
    vertices[3] = (Vec3){ width, height, depth };

    texCoord[0] = (Vec2){ 0.0, 0.0 };
    texCoord[1] = (Vec2){ texCoordH, 0.0 };
    texCoord[2] = (Vec2){ texCoordH, texCoordV };
    texCoord[3] = (Vec2){ 0.0, texCoordV };
    buildFace(vertices, color, texCoord);

    // Right
    vertices[0] = (Vec3){ 0.0f, 0.0f, 0.0f };
    vertices[1] = (Vec3){ 0.0f, 0.0f, depth };
    vertices[2] = (Vec3){ 0.0f, height, depth };
    vertices[3] = (Vec3){ 0.0f, height, 0.0f };

    texCoord[2] = (Vec2){ 0.0, 0.0 };
    texCoord[3] = (Vec2){ texCoordH, 0.0 };
    texCoord[0] = (Vec2){ texCoordH, texCoordV };
    texCoord[1] = (Vec2){ 0.0, texCoordV };
    buildFace(vertices, color, texCoord);
  }glPopMatrix();
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
    Object top = (Object){ wall.width, wall.height / 4, wall.depth / 6 };
    glTranslatef(0.0f, 3 * wall.height / 4, 5 * wall.depth / 6);
    buildBlock(top, color);
  } glPopMatrix();

  // left
  glPushMatrix(); {
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
    color = (Color){ 216.0f, 207.0f, 205.0f };
    wall = (Object){ kitchen.width, 0.0f, kitchen.depth };
    buildBlock(wall, color);
  } glPopMatrix();
  glPushMatrix(); {

    // ceil
    color = (Color){ 113.0f, 111.0f, 129.0f };
    wall = (Object){ kitchen.width, 0.0f, kitchen.depth };
    glTranslatef(0.0f, kitchen.height, 0.0f);
    buildBlock(wall, color);
  } glPopMatrix();

  // front wall
  glPushMatrix(); {
    color = (Color){ 230.0f, 233.0f, 233.0f };
    wall = (Object){ kitchen.width, kitchen.height, wallDepth };
    glTranslatef(0.0f, 0.0f, -wallDepth);
    buildBlock(wall, color);
  } glPopMatrix();

  // back wall
  glPushMatrix(); {
    color = (Color){ 230.0f, 233.0f, 233.0f };
    wall = (Object){ kitchen.width, kitchen.height, wallDepth };
    glTranslatef(0.0f, 0.0f, kitchen.depth);
    buildBackWall(wall, color);
  } glPopMatrix();

  // right wall
  glPushMatrix(); {
    color = (Color){ 124.0f, 141.0f, 148.0f };
    wall = (Object){ wallDepth, kitchen.height, kitchen.depth };
    glTranslatef(-wallDepth, 0.0f, 0.0f);
    buildBlock(wall, color);
  } glPopMatrix();

  // left wall
  glPushMatrix(); {
    color = (Color){ 124.0f, 141.0f, 148.0f };
    wall = (Object){ wallDepth, kitchen.height, kitchen.depth };
    glTranslatef(kitchen.width, 0.0f, 0.0f);
    buildLeftWall(wall, color);
  } glPopMatrix();
}

void buildDoor(Object kitchen, float doorAngle, Texture texture) {

  Color color;
  Object wall;
  Vec3 origin;

  float doorDepth = 0.125f;

  glPushMatrix(); {

    // door
    glPushMatrix(); {
      glEnable(GL_TEXTURE_2D);
      glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
      glBindTexture(GL_TEXTURE_2D, texture.id);

      color = (Color){ 240.0f, 240.0f, 240.0f };
      wall = (Object){ doorDepth, 3 * kitchen.height / 4, kitchen.depth / 6 - doorDepth };
      glTranslatef(kitchen.width + doorDepth, 0.0f, kitchen.depth - doorDepth);
      glRotatef(180.0f + doorAngle, 0.0f, 1.0f, 0.0f);
      buildBlock(wall, color);

      glFlush();
      glDisable(GL_TEXTURE_2D);
    } glPopMatrix();

    // door fix
    glPushMatrix(); {
      color = (Color){ 124.0f, 141.0f, 148.0f };
      wall = (Object){ doorDepth, 3 * kitchen.height / 4, 0.25f };
      glTranslatef(kitchen.width - 0.001f, 0.0f, kitchen.depth - doorDepth + 0.001f);
      buildBlock(wall, color);
    } glPopMatrix();
  } glPopMatrix();
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
  glBegin(GL_QUADS); // TODO: CHANGE BACK TO POLYGON
  for (int i = 0;i < object.VERTEX_COUNT;i++) {
    glNormal3f(object.NORMALS[i].x, object.NORMALS[i].y, object.NORMALS[i].z);
    glTexCoord2f(object.TEX_COORDS[i].x, object.TEX_COORDS[i].y);
    glVertex3f(object.VERTICES[i].x, object.VERTICES[i].y, object.VERTICES[i].z);
  }
  glEnd();
}

void buildFridge(Object3d fridge, int faces, Texture texture) {
  glPushMatrix(); {

    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glBindTexture(GL_TEXTURE_2D, texture.id);

    glTranslatef(1.0f, 0.0f, 14.0f);
    glScalef(0.018f, 0.018f, 0.018f);
    glRotatef(130.0f, 0.0f, 1.0f, 0.0f);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    buildObject(fridge, faces);

    glFlush();
    glDisable(GL_TEXTURE_2D);
  } glPopMatrix();
}

void buildMicrowave(Object3d microwave, int faces, Texture texture) {
  glPushMatrix(); {

    glTranslatef(0.0f, 0.0f, 2.0f);

    // support
    glPushMatrix(); {
      Object section = (Object){ 1.25f, 0.1f, 1.2f };
      glTranslatef(0.001f, 1.9f, 7.4f);
      Color color = (Color){ 200.0f, 206.0f, 212.0f };
      buildBlock(section, color);
    } glPopMatrix();

    glPushMatrix(); {

      glEnable(GL_TEXTURE_2D);
      glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
      glBindTexture(GL_TEXTURE_2D, texture.id);

      glTranslatef(0.7f, 2.0f, 8.0f);
      glScalef(0.02f, 0.02f, 0.02f);
      glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
      glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);

      buildObject(microwave, faces);

      glFlush();
      glDisable(GL_TEXTURE_2D);
    } glPopMatrix();
  } glPopMatrix();
}

void buildStove(Object3d stove, int faces, Texture texture) {
  glPushMatrix(); {

    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glBindTexture(GL_TEXTURE_2D, texture.id);

    glTranslatef(1.05f, 0.0f, 7.0f);
    glScalef(0.02f, 0.02f, 0.02f);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    buildObject(stove, faces);

    glFlush();
    glDisable(GL_TEXTURE_2D);
  } glPopMatrix();
}

void buildTap(Object3d tap, int faces, Texture texture) {
  glPushMatrix(); {
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glBindTexture(GL_TEXTURE_2D, texture.id);

    glTranslatef(0.71f, -0.3f, 8.25f);
    glScalef(0.002f, 0.002f, 0.002f);
    glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
    buildObject(tap, faces);

    glFlush();
    glDisable(GL_TEXTURE_2D);
  } glPopMatrix();
}

void buildChair(Object3d chair, int faces, Texture texture) {
  glPushMatrix(); {

    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glBindTexture(GL_TEXTURE_2D, texture.id);

    glPushMatrix(); {
      glTranslatef(2.0f, 1.0f, 1.0f);
      glScalef(0.4f, 0.4f, 0.4f);
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

    glFlush();
    glDisable(GL_TEXTURE_2D);
  } glPopMatrix();
}

void buildCabinet(Object kitchen) {
  glPushMatrix(); {

    Color color = (Color){ 221, 196, 165 };
    Color pullerColor = (Color){ 22, 35, 45 };
    Object section, door, puller;

    // bottom section
    glPushMatrix(); {
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
      section = (Object){ 1.25f, 1.5f, 7.0f };
      glTranslatef(kitchen.width - 1.25f, 3.0f, 5.0f);
      buildBlock(section, color);
    } glPopMatrix();

    // top doors
    color = (Color){ 186, 151, 124 };
    puller = (Object){ 0.05f, 0.7f, 0.05f };
    glPushMatrix(); {
      door = (Object){ 0.05f, 1.3f, 1.0f };
      glTranslatef(kitchen.width - 1.3f, 3.1f, 5.15f);
      buildBlock(door, color);
      glPushMatrix(); {
        glTranslatef(-0.05f, 0.1f, 0.85f);
        buildBlock(puller, pullerColor);
      } glPopMatrix();

      glTranslatef(0.0f, 0.0f, 1.15f);
      buildBlock(door, color);
      glPushMatrix(); {
        glTranslatef(-0.05f, 0.1f, 0.1f);
        buildBlock(puller, pullerColor);
      } glPopMatrix();

      glTranslatef(0.0f, 0.0f, 1.15f);
      buildBlock(door, color);
      glPushMatrix(); {
        glTranslatef(-0.05f, 0.1f, 0.85f);
        buildBlock(puller, pullerColor);
      } glPopMatrix();

      glTranslatef(0.0f, 0.0f, 1.15f);
      buildBlock(door, color);
      glPushMatrix(); {
        glTranslatef(-0.05f, 0.1f, 0.1f);
        buildBlock(puller, pullerColor);
      } glPopMatrix();

      glTranslatef(0.0f, 0.0f, 1.15f);
      buildBlock(door, color);
      glPushMatrix(); {
        glTranslatef(-0.05f, 0.1f, 0.85f);
        buildBlock(puller, pullerColor);
      } glPopMatrix();

      glTranslatef(0.0f, 0.0f, 1.15f);
      buildBlock(door, color);
      glPushMatrix(); {
        glTranslatef(-0.05f, 0.1f, 0.1f);
        buildBlock(puller, pullerColor);
      } glPopMatrix();
    } glPopMatrix();


    // bottom doors
    color = (Color){ 186, 151, 124 };
    glPushMatrix(); {
      door = (Object){ 0.05f, 1.3f, 1.0f };
      glTranslatef(kitchen.width - 1.3f, 0.1f, 5.15f);
      buildBlock(door, color);
      glPushMatrix(); {
        glTranslatef(-0.05f, 0.5f, 0.85f);
        buildBlock(puller, pullerColor);
      } glPopMatrix();

      glTranslatef(0.0f, 0.0f, 1.15f);
      buildBlock(door, color);
      glPushMatrix(); {
        glTranslatef(-0.05f, 0.5f, 0.1f);
        buildBlock(puller, pullerColor);
      } glPopMatrix();

      glTranslatef(0.0f, 0.0f, 1.15f);
      buildBlock(door, color);
      glPushMatrix(); {
        glTranslatef(-0.05f, 0.5f, 0.85f);
        buildBlock(puller, pullerColor);
      } glPopMatrix();

      glTranslatef(0.0f, 0.0f, 1.15f);
      buildBlock(door, color);
      glPushMatrix(); {
        glTranslatef(-0.05f, 0.5f, 0.1f);
        buildBlock(puller, pullerColor);
      } glPopMatrix();

      glTranslatef(0.0f, 0.0f, 1.15f);
      buildBlock(door, color);
      glPushMatrix(); {
        glTranslatef(-0.05f, 0.5f, 0.85f);
        buildBlock(puller, pullerColor);
      } glPopMatrix();
    } glPopMatrix();

    // drawers
    puller = (Object){ 0.05f, 0.05f, 0.6f };
    glPushMatrix(); {
      door = (Object){ 0.05f, 0.4f, 1.0f };
      glTranslatef(kitchen.width - 1.3f, 1.0f, 10.9f);
      buildBlock(door, color);
      glPushMatrix(); {
        glTranslatef(-0.05f, 0.3f, 0.2f);
        buildBlock(puller, pullerColor);
      } glPopMatrix();

      glTranslatef(0.0f, -0.45f, 0.0f);
      buildBlock(door, color);
      glPushMatrix(); {
        glTranslatef(-0.05f, 0.3f, 0.2f);
        buildBlock(puller, pullerColor);
      } glPopMatrix();

      glTranslatef(0.0f, -0.45f, 0.0f);
      buildBlock(door, color);
      glPushMatrix(); {
        glTranslatef(-0.05f, 0.3f, 0.2f);
        buildBlock(puller, pullerColor);
      } glPopMatrix();
    } glPopMatrix();

    // sink
    glPushMatrix(); {

      glTranslatef(kitchen.width - 1.0f, 1.3f, 8.0f);

      // left
      glPushMatrix(); {
        section = (Object){ 1.0f, 0.2f, 0.1f };
        glTranslatef(0.0f, 0.1f, 0.0f);
        buildBlock(section, color);
      } glPopMatrix();

      // right
      glPushMatrix(); {
        section = (Object){ 1.0f, 0.2f, 0.1f };
        glTranslatef(0.0f, 0.1f, 0.9f);
        buildBlock(section, color);
      } glPopMatrix();

      // front
      glPushMatrix(); {
        section = (Object){ 0.1f, 0.2f, 1.0f };
        glTranslatef(0.0f, 0.1f, 0.0f);
        buildBlock(section, color);
      } glPopMatrix();

      // back
      glPushMatrix(); {
        section = (Object){ 0.1f, 0.2f, 1.0f };
        glTranslatef(0.9f, 0.1f, 0.0f);
        buildBlock(section, color);
      } glPopMatrix();

      //bottom
      glPushMatrix(); {
        color = (Color){ 0.0f, 140.0f, 240.0f };
        section = (Object){ 1.0f, 0.1f, 1.0f };
        buildBlock(section, color);
      } glPopMatrix();

      // hole
      glPushMatrix(); {
        color = (Color){ 0.0f, 0.0f, 0.0f };
        section = (Object){ 0.1f, 0.1f, 0.1f };
        glTranslatef(0.5f, 0.001f, 0.45f);
        buildBlock(section, color);
      } glPopMatrix();
    } glPopMatrix();

  } glPopMatrix();
}

void buildTable(Texture texture) {
  glPushMatrix(); {
    Object section;
    Object topSection;
    Color color = (Color){ 163.0f, 128.0f, 97.0f };

    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glBindTexture(GL_TEXTURE_2D, texture.id);
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

    glFlush();
    glDisable(GL_TEXTURE_2D);
  } glPopMatrix();
}