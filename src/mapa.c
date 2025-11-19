#include "mapa.h"
#include <string.h>

const char *desenho[MAP_H] = {
    "######################################",
    "#............##.......................#",
    "#..######....##....########...........#",
    "#............##.......................#",
    "####..############..#########..########",
    "#.....................................#",
    "#..########...............#########...#",
    "#.....................................#",
    "#..########..##########..#########...#",
    "#.....................................#",
    "#..########...............#########...#",
    "#.....................................#",
    "####..############..##########..#######",
    "#.....................................#",
    "#..######....##....########...........#",
    "#............##.......................#",
    "######################################"
};

void mapa_init(Mapa *m) {
    if (!m) return;

    // copia desenho ASCII para tiles
    for (int y = 0; y < MAP_H; y++) {
        for (int x = 0; x < MAP_W; x++) {
            m->tiles[y][x] = desenho[y][x];
        }
    }

    // tenta carregar fundo (opcional). se não existir, hasFundo = 0
    // coloque assets/Mapa1.png se quiser usar a imagem real como fundo
    m->hasFundo = 0;
    // tenta carregar, mas se não puder, m->hasFundo permanece 0
    // Use Try — Raylib não tem try; LoadTexture pode falhar but usually returns a texture.
    // We'll load and set flag; if file absent you will see console log.
    m->fundo = LoadTexture("assets/Mapa1.png");
    if (m->fundo.width > 0 && m->fundo.height > 0) m->hasFundo = 1;
}

void mapa_desenhar(const Mapa *m) {
    if (!m) return;

    // se existir fundo, desenha (mantém aparência original)
    if (m->hasFundo) {
        DrawTexture(m->fundo, 0, 0, WHITE);
        return;
    }

    // caso não exista fundo, desenha tiles simples
    for (int y = 0; y < MAP_H; y++) {
        for (int x = 0; x < MAP_W; x++) {
            char c = m->tiles[y][x];
            if (c == TILE_WALL) {
                DrawRectangle(x * TILE, y * TILE, TILE, TILE, (Color){80,40,0,255});
            } else {
                // opcional: desenha grade / chão levemente visível
                DrawRectangleLines(x * TILE, y * TILE, TILE, TILE, (Color){200,200,200,80});
            }
        }
    }
}

int mapa_colisao(const Mapa *m, int tileY, int tileX) {
    if (!m) return 1;
    if (tileX < 0 || tileY < 0 || tileX >= MAP_W || tileY >= MAP_H) return 1;
    return (m->tiles[tileY][tileX] == TILE_WALL);
}

char mapa_get(const Mapa *m, int y, int x) {
    if (!m) return TILE_WALL;
    if (x < 0 || y < 0 || x >= MAP_W || y >= MAP_H) return TILE_WALL;
    return m->tiles[y][x];
}

void mapa_set(Mapa *m, int y, int x, char c) {
    if (!m) return;
    if (x < 0 || y < 0 || x >= MAP_W || y >= MAP_H) return;
    m->tiles[y][x] = c;
}

void mapa_free(Mapa *m) {
    if (!m) return;
    if (m->hasFundo) UnloadTexture(m->fundo);
    m->hasFundo = 0;
}

void mapa_carregar_png(Mapa *m, const char *arquivo) {
    if (!m) return;

    if (m->hasFundo) {
        UnloadTexture(m->fundo);
        m->hasFundo = 0;
    }

    Texture2D t = LoadTexture(arquivo);

    if (t.width > 0 && t.height > 0) {
        m->fundo = t;
        m->hasFundo = 1;
    } else {
        m->hasFundo = 0;
    }
}