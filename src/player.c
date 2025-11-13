#include "player.h"

void InitPlayer(Player *player) {
    player->texture = LoadTexture("assets/textures/player.png");
    player->position = (Vector2){400, 300}; // posição inicial no meio da tela
    player->speed = 4.0f;
}

void UpdatePlayer(Player *player) {
    // Movimento com as teclas WASD ou setas
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) player->position.x += player->speed;
    if (IsKeyDown(KEY_LEFT)  || IsKeyDown(KEY_A)) player->position.x -= player->speed;
    if (IsKeyDown(KEY_UP)    || IsKeyDown(KEY_W)) player->position.y -= player->speed;
    if (IsKeyDown(KEY_DOWN)  || IsKeyDown(KEY_S)) player->position.y += player->speed;

    // Limita o movimento para não sair da tela
    if (player->position.x < 0) player->position.x = 0;
    if (player->position.y < 0) player->position.y = 0;
    if (player->position.x > GetScreenWidth() - player->texture.width)
        player->position.x = GetScreenWidth() - player->texture.width;
    if (player->position.y > GetScreenHeight() - player->texture.height)
        player->position.y = GetScreenHeight() - player->texture.height;
}

void DrawPlayer(Player player) {
    DrawTextureEx(player.texture, player.position, 0.0f, 0.09f, WHITE);
}

void UnloadPlayer(Player *player) {
    UnloadTexture(player->texture);
}
