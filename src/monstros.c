#include "monstros.h"
#include "sprite.h"
#include <stdlib.h>

void InitMonstro(Monstro *m, int startX, int startY) {
    if (!m) return;
    m->x = startX;
    m->y = startY;
    m->ativo = false;
    m->vida = 0.0f;
    m->stepTimer = 0.0f;
    Image img = LoadImage("assets/textures/Monstro1.png");

    Color branco = (Color){255,255,255,255};
    Color transparente = (Color){0,0,0,0};

    ImageColorReplace(&img, branco, transparente);

    m->sprite = LoadTextureFromImage(img);
    UnloadImage(img);

    m->tileSize = TILE;
    m->timerVida = NULL;
}

void SpawnMonstro(Monstro *m, int startX, int startY, float vidaSegundos) {
    if (!m) return;
    m->x = startX;
    m->y = startY;
    m->ativo = true;
    m->vida = vidaSegundos;
    m->stepTimer = 0.0f;

    if (m->timerVida != NULL) {
        destruirTimer(m->timerVida);
        m->timerVida = NULL;
    }

    m->timerVida = criarTimer(3.0, true);
}

static int sign_of(int v) {
    if (v > 0) return 1;
    if (v < 0) return -1;
    return 0;
}

void UpdateMonstro(Monstro *m, Player *player, float dt, const Mapa *mapa) {
    if (!m || !m->ativo) return;

    if (m->timerVida != NULL) {
        if (estaFinalizado(m->timerVida)) {
            m->ativo = false;
            return;
        }
    }

    m->stepTimer += dt;
    const float STEP_INTERVAL = 0.25f;
    if (m->stepTimer < STEP_INTERVAL) return;
    m->stepTimer = 0.0f;

    int dx = sign_of(player->tileX - m->x);
    int dy = sign_of(player->tileY - m->y);

    int bestX = m->x;
    int bestY = m->y;

    int distX = abs(player->tileX - m->x);
    int distY = abs(player->tileY - m->y);

    if (distX >= distY) {
        if (dx != 0) {
            if (!mapa_colisao(mapa, m->y, m->x + dx)) bestX = m->x + dx;
            else if (dy != 0 && !mapa_colisao(mapa, m->y + dy, m->x)) bestY = m->y + dy;
        } else if (dy != 0 && !mapa_colisao(mapa, m->y + dy, m->x)) bestY = m->y + dy;
    } else {
        if (dy != 0) {
            if (!mapa_colisao(mapa, m->y + dy, m->x)) bestY = m->y + dy;
            else if (dx != 0 && !mapa_colisao(mapa, m->y, m->x + dx)) bestX = m->x + dx;
        } else if (dx != 0 && !mapa_colisao(mapa, m->y, m->x + dx)) bestX = m->x + dx;
    }

    if (bestX != m->x || bestY != m->y) { m->x = bestX; m->y = bestY; }

    if (m->x == player->tileX && m->y == player->tileY) player->vivo = false;
}

void DrawMonstro(const Monstro *m) {
    if (!m || !m->ativo) return;

    float scale = 0.15f;  // ajuste do tamanho do monstro

    DrawSpriteInTile(
        m->sprite,
        m->x,
        m->y,
        scale
    );
}

void FreeMonstro(Monstro *m) {
    if (!m) return;
    UnloadTexture(m->sprite);
    m->ativo = false;

    if (m->timerVida != NULL) {
        destruirTimer(m->timerVida);
        m->timerVida = NULL;
    }
}
