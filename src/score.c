#include "score.h"
#include <stdio.h>

int carregarHighscore(const char *caminho) {
    FILE *f = fopen(caminho, "r");
    if (f==NULL) {
        return 0; // se o arquivo no existir ainda, retorna 0
    }

    int hs = 0;
    if (fscanf(f, "%d", &hs) != 1){
    hs = 0;
    }
    fclose(f);
    return hs;
}

void salvarHighscore(const char *caminho, int highscore) {
    FILE *f = fopen(caminho, "w");
    if (f==NULL) {
        return; // falha ao abrir o arquivo 
    }

    fprintf(f, "%d\n", highscore);
fclose(f);
}