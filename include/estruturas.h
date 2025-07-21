#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

#define MAX_NOME 30 // Tamanho máximo para nomes, títulos, etc.

typedef struct {
    char nome[MAX_NOME];
    char telefone[MAX_NOME];
} Pessoa;

typedef struct {
    char titulo[MAX_NOME];
    char autor[MAX_NOME];
    int ano;
    int edicao;
    Pessoa dono;
} Livro;

#endif