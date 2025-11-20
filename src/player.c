#include "player.h"
#include "sprite.h"

void InitPlayer(Player *player){ 
    player->texture = LoadTexture("assets/textures/Personagem.png"); 
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
    float scale = 0.20f; // tamanho do personagem
    DrawSpriteInTile(player->texture, player->tileX, player->tileY, scale);
}

void FreePlayer(Player *player){
    UnloadTexture(player->texture);
}