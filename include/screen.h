#ifndef SCREENS_H
#define SCREENS_H
#include <stdbool.h>

typedef struct {
    int linhas, colunas;
    char **celulas; // matriz de caracteres representando o mapa, por isso o **
} Mapa;

bool mapa_carregar_png(Mapa *m, const char *arquivo); # Carrega o mapa a partir de um arquivo PNG
void mapa_desenhar(const Mapa *m); # Desenha o mapa na tela
void mapa_liberar(Mapa *m); #   Libera a memória alocada para o mapa

#endif