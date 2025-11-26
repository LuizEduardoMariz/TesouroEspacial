#ifndef MAPA_H
#define MAPA_H

#include "raylib.h"

// Ajustado para casar com PNG 1920x1080
#define MAP_W 32
#define MAP_H 18
#define TILE  60

// caracteres usados no mapa textual
#define TILE_EMPTY '.'
#define TILE_WALL  '#'
#define TILE_COIN  'C'

typedef struct {
    char tiles[MAP_H][MAP_W]; // matriz do mapa em caracteres
    Texture2D fundo;
    int hasFundo;
} Mapa;

void mapa_init_fase(Mapa *m, int fase); 
void mapa_desenhar(const Mapa *m); // desenha o fundo do mapa
int mapa_colisao(const Mapa *m, int tileY, int tileX); // verifica colisão em (tileY, tileX)
char mapa_get(const Mapa *m, int y, int x); // obtém o caractere na posição (y,x)
void mapa_set(Mapa *m, int y, int x, char c); // define o caractere na posição (y,x)
void mapa_free(Mapa *m); // libera recursos do mapa
void mapa_carregar_png(Mapa *m, const char* arquivo);

#endif
