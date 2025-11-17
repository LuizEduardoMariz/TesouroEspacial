#ifndef MAPA_H
#define MAPA_H

#include "raylib.h"

typedef struct{
    Texture2D textura;  // o mapa como imagem
}Mapa;

void mapa_init(Mapa *m);
void DrawMap(Mapa *m);
void mapa_free(Mapa *m);

#endif