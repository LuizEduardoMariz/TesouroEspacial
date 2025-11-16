#include "raylib.h"
#include "player.h"
#include "monstros.h"
#include "moedas.h"
#include "mapa.h"
#include <timer.h>

int main(void) {

    InitWindow(800, 600, "Tesouro Espacial");
    Mapa mapa;
    SetTargetFPS(60);

    Player player;
    InitPlayer(&player, 2, 2);

    Monstro monstro;
    InitMonstro(&monstro, 0, 0);

    SistemaMoedas moedas;
    InitSistemaMoedas(&moedas);

    srand(time(NULL));
    
// Spawn inicial das moedas: 10 moedas, 20s de tempo
    StartMoedas(&moedas, 10, 20.0f, &mapa);

// Monstro aparece após X segundos — você pode mudar no loop
    SpawnMonstro(&monstro, 10, 10);

    SetTargetFPS(40);
    
    
    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        int key = GetKeyPressed();


        UpdatePlayer(&player);
        UpdateMoedas(&moedas, &player, dt, &mapa);
        UpdateMonstro(&monstro, &player, dt, &mapa);

        if (!player.vivo) {
            BeginDrawing();
            ClearBackground(BLACK);
            DrawText("GAME OVER", 250, 250, 50, RED);
            EndDrawing();
            continue;
    }
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawMap(&mapa);
        DrawMoedas(&moedas);
        DrawMonstro(&monstro);
        DrawPlayer(&player);

        EndDrawing();
    }
    FreePlayer(&player);
    FreeSistemaMoedas(&moedas);
    FreeMonstro(&monstro);
    mapa_free(&mapa);

    CloseWindow();
    return 0;
}
