#include "mapa.h"

void mapa_init(Mapa *m){
    m->textura = LoadTexture("assets/Mapa1.png");
}

void DrawMap(Mapa *m){
    DrawTexture(m->textura, 0, 0, WHITE);
}

void mapa_free(Mapa *m){
    UnloadTexture(m->textura);
}