#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
#include "mapa.h"

typedef struct {
    Texture2D texture;
    Vector2 position;
    int tileX, tileY;
    float speed;
    bool vivo;
    int moedas;
} Player;

void InitPlayer(Player *player);
void UpdatePlayer(Player *player, const Mapa *mapa);
void DrawPlayer(const Player *player);
void FreePlayer(Player *player);

#endif