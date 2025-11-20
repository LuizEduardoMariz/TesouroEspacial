#ifndef SPRITE_H
#define SPRITE_H

#include "raylib.h"

// desenha qualquer sprite dentro de um tile,
// permitindo escalonamento e centralização automática
void DrawSpriteInTile(Texture2D tex, int tileX, int tileY, float scale);

#endif
