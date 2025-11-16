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
    Moeda *lista;        // vetor de moedas
    int total;           // total de moedas necessárias
    int coletadas;       
    float tempoRestante; 
    bool ativa;          // mecanica verdade
    Texture2D sprite;
    int tileSize;
} SistemaMoedas;

void InitSistemaMoedas(SistemaMoedas *s);
void StartMoedas(SistemaMoedas *s, int quantidade, float tempo, Mapa *mapa);
void UpdateMoedas(SistemaMoedas *s, Jogador *p, float dt, Mapa *mapa);
void DrawMoedas(const SistemaMoedas *s);
void FreeSistemaMoedas(SistemaMoedas *s);

#endif