#ifndef TIMER_H
#define TIMER_H

#include <stdbool.h>

typedef struct timer {
    double duracao;         // duração total em segundos
    double decorrido;       // tempo já passado
    bool ativo;             // está contando?
    bool finalizado;        // já terminou?
    struct timer *next;     // próximo na lista encadeada
} timer;

// Criação / destruição
timer *criarTimer(double duracao, bool iniciar);
void destruirTimer(timer *t);
void destruirTodosTimers(void);

// Controle
void iniciarTimer(timer *t);
void pararTimer(timer *t);
void reiniciarTimer(timer *t);

// Atualização
void atualizarTimer(timer *t, double dt);
void atualizarTodosTimers(double dt);

// Consulta
double valorTimer(const timer *t);     // tempo restante
bool estaFinalizado(const timer *t);   // terminou?

#endif