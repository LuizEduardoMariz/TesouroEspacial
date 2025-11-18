#ifndef MONSTROS_H
#define MONSTROS_H

#include "raylib.h"
#include "mapa.h"
#include "player.h"
#include "timer.h"
#include <stdbool.h>

typedef struct {
    int x, y;
    bool ativo;
    float vida;
    float stepTimer;
    Texture2D sprite;
    int tileSize;
    timer *timerVida;
} Monstro;

void InitMonstro(Monstro *m, int startX, int startY);
void SpawnMonstro(Monstro *m, int startX, int startY, float vidaSegundos);
void UpdateMonstro(Monstro *m, Player *player, float dt, const Mapa *mapa);
void DrawMonstro(const Monstro *m);
void FreeMonstro(Monstro *m);

#endif
