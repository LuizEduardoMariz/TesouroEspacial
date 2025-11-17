#include "player.h"

void InitPlayer(Player *player){ 
    player->texture = LoadTexture("assets/textures/player.png"); 
    player->speed = 2.5f;
    player->vivo = true;
    player->moedas = 0;

    // spawn inicial - escolha um tile vazio caso precise
    player->tileX = 1;
    player->tileY = 1;

    player->position.x = player->tileX * TILE;
    player->position.y = player->tileY * TILE;
}

void UpdatePlayer(Player *player, const Mapa *mapa){
    int nextX = player->tileX;
    int nextY = player->tileY;

    // usa IsKeyPressed para mover 1 tile por pressionamento
    if (IsKeyPressed(KEY_D) || IsKeyPressed(KEY_RIGHT))  nextX++;
    if (IsKeyPressed(KEY_A) || IsKeyPressed(KEY_LEFT))   nextX--;
    if (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP))     nextY--;
    if (IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN))   nextY++;

    if (!mapa_colisao(mapa, nextY, nextX)) {
        player->tileX = nextX;
        player->tileY = nextY;

        player->position.x = player->tileX * TILE;
        player->position.y = player->tileY * TILE;
    }
}

void DrawPlayer(const Player *player){
    // reduz o sprite para ficar proporcional ao tile
    DrawTextureEx(player->texture, player->position, 0.0f, 0.25f, WHITE);
}

void FreePlayer(Player *player){
    UnloadTexture(player->texture);
}