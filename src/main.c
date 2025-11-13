#include "raylib.h"
#include "player.h"

int main(void) {
    InitWindow(800, 600, "Tesouro Espacial");
    SetTargetFPS(60);

    Player player;
    InitPlayer(&player);

    while (!WindowShouldClose()) {
        UpdatePlayer(&player);

        BeginDrawing();
            ClearBackground(BLACK);
            DrawPlayer(player);
        EndDrawing();
    }

    UnloadPlayer(&player);
    CloseWindow();
    return 0;
}
