#include "raylib.h"

int main(void) {
    // Inicializa a janela
    InitWindow(800, 600, "Tesouro Espacial 🚀");
    SetTargetFPS(60);

    // Loop principal do jogo
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawText("Bem-vindo ao Tesouro Espacial!", 120, 280, 20, RAYWHITE);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
