#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GL/gl.h>
#include <GL/freeglut.h>

#include "loader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../stb_image.h"


Object3d load_obj(char* path, int faces) {

  int VERTEX_COUNT = 0;
  Vec3* VERTICES = malloc((size_t)(sizeof(Vec3) * MAX_VERTICES));
  Vec3* NORMALS = malloc((size_t)(sizeof(Vec3) * MAX_VERTICES));
  Vec2* TEX_COORDS = malloc((size_t)(sizeof(Vec2) * MAX_VERTICES));
  FILE* fp = fopen(path, "r");

  if (!fp) {
    printf("Couldn't open file %s\n", path);
    return (Object3d) { VERTEX_COUNT, VERTICES, NORMALS, TEX_COORDS };
  }


  char buffer[1024] = "";
  int vertex_count = 0;
  int normal_count = 0;
  int tex_coord_count = 0;
  Vec3 vertices[MAX_VERTICES];
  Vec3 normals[MAX_VERTICES];
  Vec2 tex_coords[MAX_VERTICES];

  while (fgets(buffer, 1024, fp)) {
    if (buffer[0] == '#') // Comment
      continue;

    char* token = strtok(buffer, " ");

    if (strcmp(token, "v") == 0) {
      // Parse vertex
      vertices[vertex_count].x = atof(strtok(NULL, " "));
      vertices[vertex_count].y = atof(strtok(NULL, " "));
      vertices[vertex_count].z = atof(strtok(NULL, " "));
      vertex_count++;
    }
    else if (strcmp(token, "vn") == 0) {
      // Parse normal vector
      normals[normal_count].x = atof(strtok(NULL, " "));
      normals[normal_count].y = atof(strtok(NULL, " "));
      normals[normal_count].z = atof(strtok(NULL, " "));
      normal_count++;
    }
    else if (strcmp(token, "vt") == 0) {
      // Parse texture coordinate
      tex_coords[tex_coord_count].x = atof(strtok(NULL, " "));
      tex_coords[tex_coord_count].y = -atof(strtok(NULL, " "));
      tex_coord_count++;
    }
    else if (strcmp(token, "f") == 0) {
      // Parse face
      int i;
      for (i = 0;i < faces;i++) {
        VERTICES[VERTEX_COUNT] = vertices[atoi(strtok(NULL, "/")) - 1];
        TEX_COORDS[VERTEX_COUNT] = tex_coords[atoi(strtok(NULL, "/")) - 1];
        NORMALS[VERTEX_COUNT] = normals[atoi(strtok(NULL, " ")) - 1];
        VERTEX_COUNT++;
      }
    }
  }

  fclose(fp);

  return (Object3d) { VERTEX_COUNT, VERTICES, NORMALS, TEX_COORDS };
}

void load_texture(char* filePath, Texture* texture) {

  texture->data = stbi_load(filePath, &texture->width, &texture->height, &texture->nrChannels, 0);

  if (!texture->data) {
    printf("Failed to load texture: %s \n", filePath);
    exit(1);
  }

}

void setupTexture(Texture* texture) {
  // glPixelStoref(GL_UNPACK_ALIGNMENT, 1);

  glGenTextures(1, &texture->id);
  glBindTexture(GL_TEXTURE_2D, texture->id);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
    GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
    GL_NEAREST);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture->width,
    texture->height, 0, GL_RGB, GL_UNSIGNED_BYTE,
    texture->data);

}

void enableMaterial(Material mtl) {
  GLfloat ambient[] = { mtl.ambient.red, mtl.ambient.green, mtl.ambient.blue, 1.0 };
  glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
  GLfloat diffuse[] = { mtl.diffuse.red, mtl.diffuse.green, mtl.diffuse.blue };
  glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
  GLfloat specular[] = { mtl.specular.red, mtl.specular.green, mtl.specular.blue };
  glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
  glMaterialf(GL_FRONT, GL_SHININESS, mtl.shininess);
}

void enableDye(Material mtl) {
  glColor3f(mtl.diffuse.red, mtl.diffuse.green, mtl.diffuse.blue);
}