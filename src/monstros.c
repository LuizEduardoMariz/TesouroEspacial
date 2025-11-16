#include "monstro.h"
#include "raylib.h"
#include <math.h>

void InitMonstro(Monstro *m, int startX, int startY) {
    m->x = startX;
    m->y = startY;
    m->ativo = false;
    m->tempoRestante = 0;

    m->sprite = LoadTexture("assets/monster.png"); #
    m->tileSize = 32; 
}

void SpawnMonstro(Monstro *m, int startX, int startY) {
    m->x = startX;
    m->y = startY;
    m->tempoRestante = 3.0f; // 3 sec perseguindo 
    m->ativo = true; 
}

void UpdateMonstro(Monstro *m, const Jogador *p, float dt, const Mapa *mapa) {
    if (!m->ativo) return;

    m->tempoRestante -= dt;
    if (m->tempoRestante <= 0) {
        m->ativo = false;
        return;
    }

    // Movimento de perseguição 
    int dx = 0, dy = 0;

    if (p->x > m->x) dx = 1;
    if (p->x < m->x) dx = -1;
    if (p->y > m->y) dy = 1;
    if (p->y < m->y) dy = -1;

    int newX = m->x + dx;
    int newY = m->y + dy;

    if (mapa_get(mapa, newY, newX) != CEL_PAREDE) {
        m->x = newX;
        m->y = newY; // para n ser invisivel
    }
    //se tocar o jogog acaba
    if (m->x == p->x && m->y == p->y) {
        ((Jogador*)p)->vivo = false;
    }
}

void DrawMonstro(const Monstro *m) { 
    if (!m->ativo) return;

    DrawTexture(m->sprite,
                m->x * m->tileSize,
                m->y * m->tileSize,
                WHITE);
}

void FreeMonstro(Monstro *m) {
    UnloadTexture(m->sprite);
}