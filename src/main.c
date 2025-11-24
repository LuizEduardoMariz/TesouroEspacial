#include "raylib.h"
#include "mapa.h"
#include "player.h"
#include "moedas.h"
#include "monstros.h"
#include "timer.h"
#include <stdlib.h>
#include <time.h>
#include <score.h>
void CarregarFase(int index, Mapa* mapa, Player* player, SistemaMoedas* moedas);

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
    //{ "assets/mapa2.png", 8, 25.0f, 2, 2  },
    //{ "assets/mapa3.png", 10, 30.0f, 2, 2 }
};

 
static const int totalFases = sizeof(fases) / sizeof(fases[0]);
static int faseAtual = 0;
void SetGameOver(bool venceu, Player* player, SistemaMoedas* moedas, int* scoreAtual, int* highscore, const char* highscoreFile, bool* gameOver, bool* scoreCalculado)
{
    // evita que seja executado mais de uma vez
    if (*gameOver) return;
    *gameOver = true;
    // se perdeu, garante que o player está morto
    if (!venceu)
        player->vivo = false;

    // calcula score apenas uma vez
    if (!(*scoreCalculado)) {
        int bonusTempo = 0;
        if (venceu && moedas->tempoRestante > 0.0f) {
            bonusTempo = (int)(moedas->tempoRestante) * 10;
        }
        *scoreAtual = moedas->coletadas * 100 + bonusTempo;
        if (*scoreAtual > *highscore) {
            *highscore = *scoreAtual;
            salvarHighscore(highscoreFile, *highscore);
        }
        *scoreCalculado = true;
    }
}
void CheckEndConditions(timer* timerFase, Player* player, SistemaMoedas* moedas, int* faseAtual, int totalFases, Mapa* mapa, const char* highscoreFile, int* scoreAtual, int* highscore, bool* gameOver, bool* venceu, bool* scoreCalculado)
{
    if (*gameOver) return;
    // timer acabou -> derrota  
    if (estaFinalizado(timerFase)) {
        *venceu = false;
        SetGameOver(false, player, moedas, scoreAtual, highscore,
                    highscoreFile, gameOver, scoreCalculado);
        return;
    }
    // player morreu por monstro/colisão
    if (!player->vivo) {
        *venceu = false;
        SetGameOver(false, player, moedas, scoreAtual, highscore,
                    highscoreFile, gameOver, scoreCalculado);
        return;
    }
    // coletou todas as moedas da fase → avançar ou terminar
    if (!moedas->ativa && moedas->coletadas == moedas->total) {
        (*faseAtual)++;
        if (*faseAtual >= totalFases) {
            // venceu
            *venceu = true;
            SetGameOver(true, player, moedas, scoreAtual, highscore,
                        highscoreFile, gameOver, scoreCalculado);
        } else {
            // Carrega a próxima fase normalmente
            CarregarFase(*faseAtual, mapa, player, moedas);
        }
    }
}

void CarregarFase(int index, Mapa* mapa, Player* player, SistemaMoedas* moedas)
{
    if (index < 0 || index >= totalFases) return;

    // libera mapa antigo (se houver)
    mapa_free(mapa);

    // ⚠ IMPORTANTE: inicializa o mapa ASCII antes de carregar o PNG
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

    Player player   ;
    InitPlayer(&player); //inicializa player; valores serão sobrescritos por CarregarFase
    player.vivo = true;

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
    bool scoreCalculado = false;

while (!WindowShouldClose())
{
    float dt = GetFrameTime();

    if (!gameOver) {
    atualizarTodosTimers((double)dt);

    UpdatePlayer(&player, &mapa);
    UpdateMonstro(&monstro, &player, dt, &mapa);
    UpdateMoedas(&moedas, &player, dt, &mapa);

    CheckEndConditions(timerFase,
                       &player,
                       &moedas,
                       &faseAtual,  
                       totalFases,
                       &mapa,
                       HIGHSCORE_FILE,
                       &scoreAtual,
                       &highscore,
                       &gameOver,
                       &venceu,
                       &scoreCalculado);
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

return 0;
}