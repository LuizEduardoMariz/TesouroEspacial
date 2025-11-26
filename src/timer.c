#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "timer.h"

static timer *head = NULL; // cabeça da lista encadeada

static void adicionarTimer(timer *t) {
    if (t == NULL) {
        return;
    }

    t->next = head;
    head = t;
}

static void removerDaLista(timer *t) {
    if (t == NULL) {
        return;
    }

    if (head == NULL) {
        return;
    }

    if (head == t) {
        head = head->next;
        return;
    }

    timer *atual = head;

    while (atual->next != NULL && atual->next != t) {
        atual = atual->next;
    }

    if (atual->next == t) {
        atual->next = t->next;
    }
}

timer *criarTimer(double duracao, bool iniciar) {
    timer *t = (timer *)malloc(sizeof(timer));
    if (t == NULL) {
        return NULL;
    }

    if (duracao > 0.0) {
        t->duracao = duracao;
    } else {
        t->duracao = 0.0;
    }

    t->decorrido = 0.0;
    t->ativo = iniciar;
    t->finalizado = false;
    t->next = NULL;

    adicionarTimer(t);
    return t;
}

void destruirTimer(timer *t) {
    if (t == NULL) {
        return;
    }

    removerDaLista(t);
    free(t);
}

void destruirTodosTimers(void) {
    timer *atual = head;

    while (atual != NULL) {
        timer *proximo = atual->next;
        free(atual);
        atual = proximo;
    }

    head = NULL;
}

void iniciarTimer(timer *t) {
    if (t == NULL) {
        return;
    }

    t->ativo = true;
}

void pararTimer(timer *t) {
    if (t == NULL) {
        return;
    }

    t->ativo = false;
}

void reiniciarTimer(timer *t) {
    if (t == NULL) {
        return;
    }

    t->decorrido = 0.0;
    t->finalizado = false;
    t->ativo = true;
}

void atualizarTimer(timer *t, double dt) {
    if (t == NULL) {
        return;
    }

    if (t->ativo == false) {
        return;
    }

    if (t->finalizado == true) {
        return;
    }

    if (dt > 0.0) {
        t->decorrido += dt;
    }

    if (t->decorrido >= t->duracao) {
        t->decorrido = t->duracao;
        t->finalizado = true;
        t->ativo = false;
    }
}

void atualizarTodosTimers(double dt) {
    timer *atual = head;

    while (atual != NULL) {
        atualizarTimer(atual, dt);
        atual = atual->next;
    }
}

double valorTimer(const timer *t) {
    if (t == NULL) {
        return 0.0;
    }

    double restante = t->duracao - t->decorrido;

    if (restante < 0.0) {
        restante = 0.0;
    }

    return restante;
}

bool estaFinalizado(const timer *t) {
    if (t == NULL) {
        return false;
    }

    return t->finalizado;
}


