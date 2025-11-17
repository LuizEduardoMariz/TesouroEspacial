#include "raylib.h"
#include "mapa.h"
#include "player.h"
#include "moedas.h"
#include "monstros.h"
#include <stdlib.h>
#include <time.h>

int main(void) {
    const int screenW = MAP_W * TILE;
    const int screenH = MAP_H * TILE;

    InitWindow(screenW, screenH, "Tesouro Espacial");
    SetTargetFPS(60);

    Mapa mapa;
    mapa_init(&mapa);

    Player player;
    InitPlayer(&player);

    SistemaMoedas moedas;
    InitSistemaMoedas(&moedas);
    srand((unsigned)time(NULL));
    StartMoedas(&moedas, 10, 20.0f, &mapa);

    Monstro monstro;
    InitMonstro(&monstro, 10, 10);
    SpawnMonstro(&monstro, 10, 10, 30.0f);

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        UpdatePlayer(&player, &mapa);
        UpdateMoedas(&moedas, &player, dt, &mapa);
        UpdateMonstro(&monstro, &player, dt, &mapa);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        mapa_desenhar(&mapa);
        DrawMoedas(&moedas);
        DrawMonstro(&monstro);
        DrawPlayer(&player);

        DrawText(TextFormat("Moedas: %d/%d", moedas.coletadas, moedas.total), 8, 8, 20, YELLOW);
        if (!player.vivo) DrawText("GAME OVER", screenW/2 - 100, screenH/2 - 20, 40, RED);

        EndDrawing();
    }

    FreePlayer(&player);
    FreeSistemaMoedas(&moedas);
    FreeMonstro(&monstro);
    mapa_free(&mapa);

    CloseWindow();
    return 0;
}
