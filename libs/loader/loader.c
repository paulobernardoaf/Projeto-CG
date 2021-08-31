#include <stdio.h>
#include <string.h>
#include <GL/gl.h>
#include <GL/freeglut.h>

#include "loader.h"


Object3d load_obj(char* path, int faces) {

  int VERTEX_COUNT = 0;
  Vec3 VERTICES[MAX_VERTICES];
  Vec3 NORMALS[MAX_VERTICES];
  Vec2 TEX_COORDS[MAX_VERTICES];

  FILE* fp = fopen(path, "r");

  if (!fp)
    return (Object3d) { VERTEX_COUNT, VERTICES, NORMALS, TEX_COORDS };;

  char buffer[512] = "";
  int vertex_count = 0;
  int normal_count = 0;
  int tex_coord_count = 0;
  Vec3 vertices[MAX_VERTICES];
  Vec3 normals[MAX_VERTICES];
  Vec2 tex_coords[MAX_VERTICES];

  while (fgets(buffer, 512, fp)) {
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

  return (Object3d){VERTEX_COUNT, VERTICES, NORMALS, TEX_COORDS};
}