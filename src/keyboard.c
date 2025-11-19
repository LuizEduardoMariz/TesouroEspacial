#include "raylib.h"
#include "keyboard.h"

static int peekCharacter = 0;

void keyboardInit(void){
}

void keyboardDestroy(void){
}

int keyboardHit(void){
    if (peekCharacter != 0) {
        return 1;
    }

    int key = GetKeyPressed();

    if (key != 0) {
        peekCharacter = key;
        return 1;
    }

    return 0;
}

int keyboardRead(void){
    if (peekCharacter != 0) {
        int key = peekCharacter;
        peekCharacter = 0;
        return key;
    }

    return GetKeyPressed();
}