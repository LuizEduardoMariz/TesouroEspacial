#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

typedef struct {
    Texture2D texture;   // imagem do player
    Vector2 position;    // posição x, y
    float speed;         // velocidade de movimento
} Player;

void InitPlayer(Player *player);
void UpdatePlayer(Player *player);
void DrawPlayer(Player player);
void UnloadPlayer(Player *player);

#endif