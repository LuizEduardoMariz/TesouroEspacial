#ifndef FASES_H
#define FASES_H

typedef struct {
    const char* arquivoMapa; //# caminho para o arquivo de mapa
    int moedasNecessarias; //# número de moedas necessárias para completar a fase
    float tempoLimite; //# tempo limite em segundos
    int startX, startY; //# posição inicial do jogador
} Fase;

#endif