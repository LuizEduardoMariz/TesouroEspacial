#include "player.h"

void InitPlayer(Player *player) { 
    player->texture = LoadTexture("assets/textures/player.png"); 
    player->pos = (Vector2){400, 300};      
    player->vel = (Vector2){0, 0};           
    player->len = (Vector2){                 
        player->texture.width * 1.0f,
        player->texture.height * 1.0f
    };
    player->speed = 4.0f;
}
#
void UpdatePlayer(Player *player) {
        player->vel.x = 0;
    player->vel.y = 0;

    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))  player->vel.x =  player->speed;
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))   player->vel.x = -player->speed;
    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))     player->vel.y = -player->speed;
    if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))   player->vel.y =  player->speed;
    float screenW = GetScreenWidth(); 
    float screenH = GetScreenHeight(); #verificar os limites

#verficar as bordas da tela
    if (player->pos.x + player->vel.x >= 0 &&
        player->pos.x + player->len.x + player->vel.x <= screenW) {
        player->pos.x += player->vel.x; 
    }
    if (player->pos.y + player->vel.y >= 0 &&
        player->pos.y + player->len.y + player->vel.y <= screenH) {
        player->pos.y += player->vel.y;
    }
}

void DrawPlayer(Player player) {
    DrawTextureEx(player.texture, player.pos, 0.0f, 1.0f, WHITE); #desenha o player na tela
}

void UnloadPlayer(Player *player) {     #libera a textura do player
    UnloadTexture(player->texture);
}