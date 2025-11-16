#include "moedas.h"
#include <stdlib.h>

void InitSistemaMoedas(SistemaMoedas *s) {
    s->lista = NULL;
    s->total = 0;
    s->coletadas = 0;
    s->tempoRestante = 0;
    s->ativa = false;
    s->tileSize = 32;

    s->sprite = LoadTexture("assets/moeda.png");
}

void StartMoedas(SistemaMoedas *s, int quantidade, float tempo, Mapa *mapa) {
    if (s->lista) free(s->lista);

    s->lista = malloc(sizeof(Moeda) * quantidade);
    s->total = quantidade;
    s->coletadas = 0;
    s->tempoRestante = tempo;
    s->ativa = true;

    // spawn das moedas em posições aleatórias do mapa
    for (int i = 0; i < quantidade; i++) {
        int x, y;

        do {
            x = rand() % mapa->colunas;
            y = rand() % mapa->linhas;
        } while (mapa_get(mapa, y, x) != CEL_VAZIA);

        s->lista[i].x = x;
        s->lista[i].y = y;
        s->lista[i].ativa = true;

        mapa_set(mapa, y, x, CEL_MOEDA);
    }
}

void UpdateMoedas(SistemaMoedas *s, Jogador *p, float dt, Mapa *mapa) {
    if (!s->ativa) return;

    s->tempoRestante -= dt;

    //acabou o tempo gameover
    if (s->tempoRestante <= 0 && s->coletadas < s->total) {
        p->vivo = false; // GAME OVER
        s->ativa = false;
        return;
    }

    //verifica se pegou moeda
    for (int i = 0; i < s->total; i++) {
        Moeda *m = &s->lista[i];

        if (!m->ativa) continue;

        if (p->x == m->x && p->y == m->y) {
            m->ativa = false;
            s->coletadas++;
            p->moedas++;
            mapa_set(mapa, m->y, m->x, CEL_VAZIA);
        }
    }

    //se pegar tudo, concluido
    if (s->coletadas == s->total) {
        s->ativa = false;
    }
}

void DrawMoedas(const SistemaMoedas *s) {
    if (!s->ativa) return;

    for (int i = 0; i < s->total; i++) {
        if (!s->lista[i].ativa) continue;

        DrawTexture(
            s->sprite,
            s->lista[i].x * s->tileSize,
            s->lista[i].y * s->tileSize,
            WHITE
        );
    }

    //desenha o timer
    DrawText(TextFormat("Tempo: %.1f", s->tempoRestante),
             10, 10, 30, YELLOW);

    DrawText(TextFormat("Coletadas: %d / %d", s->coletadas, s->total),
             10, 50, 30, YELLOW);
}

void FreeSistemaMoedas(SistemaMoedas *s) {
    if (s->lista)
        free(s->lista);

    UnloadTexture(s->sprite);
}