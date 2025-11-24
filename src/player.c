#include "player.h"
#include "sprite.h"

void InitPlayer(Player *player){ 

    Image img = LoadImage("assets/textures/Personagem.png");

    // Cor do fundo (branco puro)
    Color bg = (Color){255, 255, 255, 255};

    // Cor transparente
    Color transparent = (Color){0, 0, 0, 0};

    // Remove o fundo branco
    ImageColorReplace(&img, bg, transparent);

    // Converte para textura
    player->texture = LoadTextureFromImage(img);
    UnloadImage(img);

    // Configurações normais do player
    player->speed = 2.5f;
    player->vivo = true;
    player->moedas = 0;

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
    float scale = 0.15f; // tamanho do personagem
    DrawSpriteInTile(player->texture, player->tileX, player->tileY, scale);
}

void FreePlayer(Player *player){
    UnloadTexture(player->texture);
}