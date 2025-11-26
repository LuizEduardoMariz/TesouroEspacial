#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "raylib.h"

void keyboardInit(void);
void keyboardDestroy(void);
int keyboardHit(void); // retorna 1 se uma tecla foi pressionada, 0 caso contrário
int keyboardRead(void); 

#endif