#ifndef MOEDAS_H
#define MOEDAS_H

#include "mapa.h"
#include "player.h"
#include "raylib.h"

typedef struct {
    int x, y;
    bool ativa;
} Moeda;

typedef struct {
    Moeda *lista;
    int total;
    int coletadas;
    float tempoRestante;
    bool ativa;
    Texture2D sprite;
} SistemaMoedas;

void InitSistemaMoedas(SistemaMoedas *s);
void StartMoedas(SistemaMoedas *s, int quantidade, float tempo, Mapa *mapa);
void UpdateMoedas(SistemaMoedas *s, Player *p, float dt, Mapa *mapa);
void DrawMoedas(const SistemaMoedas *s);
void FreeSistemaMoedas(SistemaMoedas *s);

#endif