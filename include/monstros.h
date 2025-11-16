#ifndef MONSTRO_H
#define MONSTRO_H
#include "raylib.h"

#include "mapa.h"

typedef struct {
    int x, y;
    bool ativo;
    float tempoRestante; // 3 segundos
    Texture2D sprite;
    int tileSize;
} Monstro;

void InitMonstro(Monstro *m, int startX, int startY);
void SpawnMonstro(Monstro *m, int startX, int startY);
void UpdateMonstro(Monstro *m, const Player *p, float dt, const Mapa *mapa);
void DrawMonstro(const Monstro *m);
void FreeMonstro(Monstro*m);

#endif