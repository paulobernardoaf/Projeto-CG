#ifndef _ANIMATION_H_
#define _ANIMATION_H_

// OPEN = 1; OPENING = 2; CLOSED = 3; CLOSING = 4
extern int DOOR_STEP;
extern float DOOR_ANGLE;

extern int WINDOW_STEP;
extern float WINDOW_ANGLE;

extern float FAN_ROTATION;

extern void handleDoor();

extern void handleWindow();

extern void handleDoorAnimation();

extern void handleWindowAnimation();

extern void handleFanAnimation();

#endif