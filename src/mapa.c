#include "mapa.h"
#include <string.h>

static const char *desenhoFase1[MAP_H] = {
    "................................",
    "....................########....",
    "......######....................",
    "..................##......##....",
    "..##..............##......##....",
    "..##..............##............",
    "..##......######................",
    "..##..........##................",
    "................................",
    "....####........................",
    "......##......................##",
    "........##..............####..##",
    "..........##..........##........",
    "##..................####..##....",
    "##..................####..##....",
    "##..................##..........",
    "......................######....",
    "................................"
};

static const char *desenhoFase2[MAP_H] = {
    "##########....##....############",
    "#.............##...............#",
    "#......###....##.....####..###.#",
    "#.....####....##..##.####..###.#",
    "..##..............##...........#",
    "..##..............##...........#",
    "..##......######........##.....#",
    "..##..........###.......######..",
    "............##.....###..........",
    "....####....##.....###..........",
    "#.....##......#####.............",
    "#....#...........##.....####....",
    "#....#.....##.........##........",
    "#.####....###.##.##.####...###.#",
    "#.###..#......##.##.##.....###.#",
    "#.###..##.....##.##.##.....###.#",
    "#.............##.##............#",
    "############..##.##...##########"
};
//inicializa o mapa com o desenho da fase
void mapa_init_fase(Mapa *m, int fase) {
    if (!m) return;

    const char **src = (fase == 0) ? desenhoFase1 : desenhoFase2;

    for (int y = 0; y < MAP_H; y++) {
        for (int x = 0; x < MAP_W; x++) {
            m->tiles[y][x] = src[y][x];
        }
    }

    m->hasFundo = 0;
}

// Desenhar PNG da fase
void mapa_desenhar(const Mapa *m) {
    if (!m) return;

    if (m->hasFundo)
        DrawTexture(m->fundo, 0, 0, WHITE);
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

    if (m->hasFundo)
        UnloadTexture(m->fundo);

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
    }
}