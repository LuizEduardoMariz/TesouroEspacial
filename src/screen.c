#include "raylib.h"
#include <stdlib.h>

bool mapa_carregar_png(Mapa *m, const char *arquivo) {
    Image img = LoadImage(arquivo); # Carrega a imagem do mapa
    m->linhas = img.height; # Define o número de linhas do mapa
    m->colunas = img.width; # Define o número de colunas do mapa

    m->celulas = malloc(m->linhas * sizeof(char *)); # Aloca memória para as linhas do mapa
    for (int i = 0; i < m->linhas; i++) { 
        m->celulas[i] = malloc(m->colunas); 
        for (int j = 0; j < m->colunas; j++) {
            Color c = GetImageColor(img, j, i); # Obtém a cor do pixel na posição (j, i)
            m->celulas[i][j] = (c.r < 128 && c.g < 128 && c.b < 128) ? '#' : ' '; # Define a célula como parede ou espaço
        }
    }

    UnloadImage(img); # Libera a imagem carregada
    return true;
}
void mapa_desenhar(const Mapa *m) { # Desenha o mapa na tela
    for (int i = 0; i < m->linhas; i++) {
        for (int j = 0; j < m->colunas; j++) {
            if (m->celulas[i][j] == '#') {
                DrawRectangle(j * 32, i * 32, 32, 32, DARKBROWN); # Desenha uma parede
            }
        }
    }
}

void mapa_liberar(Mapa *m) {   #
    if (!m || !m->celulas) return;
    for (int i = 0; i < m->linhas; i++) {
        free(m->celulas[i]);
    }
    free(m->celulas);
    m->celulas = NULL;
}
