#include "animation.h"

void handleDoor() {
  if (DOOR_STEP == 1) { // open
    DOOR_STEP = 4; // closing
  }
  else if (DOOR_STEP == 3) { // closed 
    DOOR_STEP = 2; // opening
  }
}

void handleWindow() {
  if (WINDOW_STEP == 1) { // open
    WINDOW_STEP = 4; // closing
  }
  else if (WINDOW_STEP == 3) { // closed 
    WINDOW_STEP = 2; // opening
  }
}

void handleDoorAnimation() {
  if (DOOR_STEP == 2) { // opening
    DOOR_ANGLE += 1.0f;
  }
  else if (DOOR_STEP == 4) { // closing
    DOOR_ANGLE -= 1.0f;
  }

  if (DOOR_ANGLE >= 90.0f) {
    DOOR_STEP = 1; // open
  }
  else if (DOOR_ANGLE <= 0.0f) {
    DOOR_STEP = 3; // closed
  }
}

void handleWindowAnimation() {
  if (WINDOW_STEP == 2) { // opening
    WINDOW_ANGLE -= 1.0f;
  }
  else if (WINDOW_STEP == 4) { // closing
    WINDOW_ANGLE += 1.0f;
  }

  if (WINDOW_ANGLE <= -65.0f) {
    WINDOW_STEP = 1; // open
  }
  else if (WINDOW_ANGLE >= 0.0f) {
    WINDOW_STEP = 3; // closed
  }
}
