#include "raylib.h"
#include "mapa.h"
#include "player.h"
#include "moedas.h"
#include "monstros.h"
#include "timer.h"
#include <stdlib.h>
#include <time.h>

//STRUCT FASES
typedef struct {
    const char* arquivoMapa;
    int moedasNecessarias;
    float tempoLimite;
    int startX, startY;
} Fase;

// DEFINIR AS FASES AQUI
static Fase fases[] = {
    { "assets/mapa1.png", 5, 20.0f, 2, 2 },
    { "assets/mapa2.png", 8, 25.0f, 2, 2 },
    { "assets/mapa3.png", 10, 30.0f, 2, 2 }
};

 
static const int totalFases = sizeof(fases) / sizeof(fases[0]);
static int faseAtual = 0;


void CarregarFase(int index, Mapa* mapa, Jogador* jogador, SistemaMoedas* moedas)
{
    if (index < 0 || index >= totalFases) return;

    // libera mapa antigo (se houver)
    mapa_liberar(mapa);

    // carrega novo mapa a partir do png (sua função)
    mapa_carregar_png(mapa, fases[index].arquivoMapa);

    // posiciona jogador na posição inicial da fase
    jogador->x = fases[index].startX;
    jogador->y = fases[index].startY;

    // inicia sistema de moedas para a fase
    StartMoedas(moedas,
                fases[index].moedasNecessarias,
                fases[index].tempoLimite,
                mapa);
}

// --------------------------
// main
// --------------------------
int main(void)
{
    // Ajuste de resolução: utiliza macros MAP_W, MAP_H, TILE do seu projeto
    const int screenW = MAP_W * TILE;
    const int screenH = MAP_H * TILE;

    InitWindow(screenW, screenH, "Tesouro Espacial");
    SetTargetFPS(60);

    srand((unsigned)time(NULL));

    // Objetos do jogo
    Mapa mapa;
    // Não chamei mapa_init porque suas funções mostradas usam mapa_carregar_png / mapa_liberar.
    // Apenas inicializo campos se necessário; mapa_carregar_png vai preencher linhas/colunas.
    mapa.celulas = NULL;
    mapa.linhas = 0;
    mapa.colunas = 0;

    Jogador jogador;
    InitPlayer(&jogador, 0, 0); //inicializa player; valores serão sobrescritos por CarregarFase

    SistemaMoedas moedas;
    InitSistemaMoedas(&moedas);

    Monstro monstro;
    InitMonstro(&monstro, 10, 10); 
    SpawnMonstro(&monstro, 10, 10);

    timer *timerFase = criarTimer(60.0, true);

    faseAtual = 0;
    CarregarFase(faseAtual, &mapa, &jogador, &moedas);

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();

        //ATUALIZA O TIMER DA FASE
        atualizarTodosTimers((double)dt);

        // SE O TIMER ACABAR, FINALIZA O JOGO
        if (estaFinalizado(timerFase)) {
            jogador.vivo = false;
        }

        int key = GetKeyPressed(); 

        //atualiza
        UpdatePlayer(&jogador, key, &mapa);
        UpdateMoedas(&moedas, &jogador, dt, &mapa);
        UpdateMonstro(&monstro, &jogador, dt, &mapa);

        // Verifica se o jogador coletou todas as moedas necessárias para avançar
        if (!moedas.ativa && moedas.coletadas == moedas.total) {
            faseAtual++;
            if (faseAtual >= totalFases) {
               #SE COMPLETOU O JOGO, WIN
                jogador.vivo = false;
            } else {
                CarregarFase(faseAtual, &mapa, &jogador, &moedas);
            }
        }

        BeginDrawing(); 
            ClearBackground(RAYWHITE); // cor de fundo

            mapa_desenhar(&mapa);
            DrawMoedas(&moedas);
            DrawMonstro(&monstro);
            DrawPlayer(&jogador);

            DrawText(TextFormat("Moedas: %d/%d", moedas.coletadas, moedas.total), 8, 8, 20, YELLOW);

            if (!jogador.vivo) {
                DrawText("GAME OVER", screenW/2 - 100, screenH/2 - 20, 40, RED);
            }
        EndDrawing();
    }

    FreePlayer(&jogador);
    FreeSistemaMoedas(&moedas);
    FreeMonstro(&monstro);
    mapa_liberar(&mapa);

    destruirTodosTimers();
    CloseWindow();

    return 0;
}
