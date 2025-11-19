#ifndef MAPA_H
#define MAPA_H

#include "raylib.h"

#define MAP_W 38
#define MAP_H 17
#define TILE  64

// caracteres usados no mapa textual
#define TILE_EMPTY '.'
#define TILE_WALL  '#'
#define TILE_COIN  'C'

typedef struct {
    char tiles[MAP_H][MAP_W];
    Texture2D fundo;    // opcional: se existir assets/Mapa1.png
    int hasFundo;
} Mapa;

void mapa_init(Mapa *m);
void mapa_desenhar(const Mapa *m);
int mapa_colisao(const Mapa *m, int tileY, int tileX);
char mapa_get(const Mapa *m, int y, int x);
void mapa_set(Mapa *m, int y, int x, char c);
void mapa_free(Mapa *m);
void mapa_carregar_png(Mapa *m, const char* arquivo);

#endif