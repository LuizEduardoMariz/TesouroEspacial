#include "moedas.h"
#include "sprite.h"
#include <stdlib.h>

void InitSistemaMoedas(SistemaMoedas *s){
    s->lista = NULL;
    s->total = 0;
    s->coletadas = 0;
    s->tempoRestante = 0;
    s->ativa = false;
    s->sprite = LoadTexture("assets/textures/Moeda.png");
}

void StartMoedas(SistemaMoedas *s, int quantidade, float tempo, Mapa *mapa){
    if (s->lista) free(s->lista);
    s->lista = malloc(sizeof(Moeda) * quantidade);
    s->total = quantidade;
    s->coletadas = 0;
    s->tempoRestante = tempo;
    s->ativa = true;

    for (int i = 0; i < quantidade; i++){
        int x, y;
        do {
            x = rand() % MAP_W;
            y = rand() % MAP_H;
        } while (mapa_get(mapa, y, x) != TILE_EMPTY);

        s->lista[i].x = x;
        s->lista[i].y = y;
        s->lista[i].ativa = true;

        mapa_set(mapa, y, x, TILE_COIN);
    }
}

void UpdateMoedas(SistemaMoedas *s, Player *p, float dt, Mapa *mapa){
    if (!s->ativa) return;

    s->tempoRestante -= dt;

    if (s->tempoRestante <= 0 && s->coletadas < s->total){
        p->vivo = false;
        s->ativa = false;
        return;
    }

    for (int i = 0; i < s->total; i++){
        Moeda *m = &s->lista[i];
        if (!m->ativa) continue;
        if (p->tileX == m->x && p->tileY == m->y){
            m->ativa = false;
            s->coletadas++;
            p->moedas++;
            mapa_set(mapa, m->y, m->x, TILE_EMPTY);
        }
    }

    if (s->coletadas == s->total) s->ativa = false;
}

void DrawMoedas(const SistemaMoedas *s){
    if (!s->ativa) return;

    float scale = 0.10f; // ajuste livre

    for (int i = 0; i < s->total; i++){
        if (!s->lista[i].ativa) continue;

        DrawSpriteInTile(
            s->sprite,
            s->lista[i].x,
            s->lista[i].y,
            scale
        );
    }
}

void FreeSistemaMoedas(SistemaMoedas *s){
    if (s->lista) free(s->lista);
    UnloadTexture(s->sprite);
}
