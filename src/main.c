#include "raylib.h"
#include "mapa.h"
#include "player.h"
#include "moedas.h"
#include "monstros.h"
#include "timer.h"
#include <stdlib.h>
#include <time.h>
#include <score.h>

//STRUCT FASES
typedef struct {
    const char* arquivoMapa;
    int moedasNecessarias;
    float tempoLimite;
    int startX, startY;
} Fase;

// DEFINIR AS FASES AQUI
static Fase fases[] = {
    { "assets/textures/Mapa1.png", 5, 20.0f, 2, 2 },
    //{ "assets/mapa2.png", 8, 25.0f, 2, 2 },
    //{ "assets/mapa3.png", 10, 30.0f, 2, 2 }
};

 
static const int totalFases = sizeof(fases) / sizeof(fases[0]);
static int faseAtual = 0;


void CarregarFase(int index, Mapa* mapa, Player* player, SistemaMoedas* moedas)
{
    if (index < 0 || index >= totalFases) return;

    // libera mapa antigo (se houver)
    mapa_free(mapa);

    // ⚠️ IMPORTANTE: inicializa o mapa ASCII antes de carregar o PNG
    mapa_init(mapa);

    // carrega o fundo visual da fase
    mapa_carregar_png(mapa, fases[index].arquivoMapa);

    // posiciona jogador na posição inicial da fase
    player->tileX = fases[index].startX;
    player->tileY = fases[index].startY;

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
    //mapa.celulas = NULL;
    //mapa.linhas = 0;
    //mapa.colunas = 0;

    Player jogador;
    InitPlayer(&player); //inicializa player; valores serão sobrescritos por CarregarFase

    SistemaMoedas moedas;
    InitSistemaMoedas(&moedas);

    Monstro monstro;
    InitMonstro(&monstro, 10, 10); 
    SpawnMonstro(&monstro, 10, 10, 5.0f);

    timer *timerFase = criarTimer(60.0, true);

    faseAtual = 0;
    CarregarFase(faseAtual, &mapa, &player, &moedas);

    const char* HIGHSCORE_FILE = "highscore.txt";
    int highscore = carregarHighscore(HIGHSCORE_FILE);
    int scoreAtual = 0;
    bool gameOver = false;
    bool venceu = false;
    bool scoreCalculado = false;

while (!WindowShouldClose())
    {
        float dt = GetFrameTime();

        if (!gameOver) {
            // ATUALIZA O TIMER DA FASE
            atualizarTodosTimers((double)dt);

            // SE O TIMER ACABAR, DERROTA
            if (estaFinalizado(timerFase)) {
                player.vivo = false;
                gameOver = true;
                venceu = false;
            }

            //int key = GetKeyPressed(); 

            // atualiza entidades
            UpdatePlayer(&player, &mapa);
            UpdateMoedas(&moedas, &player, dt, &mapa);
            UpdateMonstro(&monstro, &player, dt, &mapa);

            // se o jogador morreu por monstro/tempo das moedas
            if (!player.vivo && !gameOver) {
                gameOver = true;
                venceu = false;
            }

            // Verifica se o jogador coletou todas as moedas necessárias para avançar
            if (!moedas.ativa && moedas.coletadas == moedas.total && !gameOver) {
                faseAtual++;
                if (faseAtual >= totalFases) {
                    // COMPLETOU O JOGO -> VITÓRIA
                    gameOver = true;
                    venceu = true;
                } else {
                    CarregarFase(faseAtual, &mapa, &player, &moedas);
                }
            }

            // Se o jogo acabou AGORA, calcula score e highscore
            if (gameOver && !scoreCalculado) {
                int bonusTempo = 0;
                if (venceu && moedas.tempoRestante > 0.0f) {
                    bonusTempo = (int)moedas.tempoRestante * 10;
                }

                // regra de pontuação simples:
                scoreAtual = moedas.coletadas * 100 + bonusTempo;

                if (scoreAtual > highscore) {
                    highscore = scoreAtual;
                    salvarHighscore(HIGHSCORE_FILE, highscore);
                }

                scoreCalculado = true;
            }
        }


        BeginDrawing(); 
            ClearBackground(RAYWHITE); // cor de fundo

            mapa_desenhar(&mapa);
            DrawMoedas(&moedas);
            DrawMonstro(&monstro);
            DrawPlayer(&player);

            DrawText(TextFormat("Moedas: %d/%d", moedas.coletadas, moedas.total),
                     8, 8, 20, YELLOW);

            DrawText(TextFormat("Highscore: %d", highscore),
                     8, 32, 20, YELLOW);

            if (gameOver) {
                DrawText(TextFormat("Score: %d", scoreAtual),
                         8, 56, 20, YELLOW);

                if(venceu){
                    DrawText("VOCE VENCEU!",
                            screenW/2 - 140, screenH/2 - 20, 40,
                            GREEN);
                }else{
                   DrawText("GAME OVER",
                            screenW/2 - 140, screenH/2 - 20, 40,
                            RED);
                }
            }
        EndDrawing();
    }

    FreePlayer(&player);
    FreeSistemaMoedas(&moedas);
    FreeMonstro(&monstro);
    mapa_free(&mapa);

    destruirTodosTimers();
    CloseWindow();

    return 0;
}

