#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "raylib.h"

void keyboardInit(void);
void keyboardDestroy(void);
int keyboardHit(void);
int keyboardRead(void);

#endif