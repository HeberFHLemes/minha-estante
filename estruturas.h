#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

#define MAX_NOME 30 // Tamanho máximo para nomes, títulos, etc.
#define MAX_LIVROS 20 // Máximo de livros em uma estante

typedef struct {
    char titulo[MAX_NOME];
    char autor[MAX_NOME];
    int ano;
    int edicao;
} Livro;

typedef struct {
    char nome[MAX_NOME];
    char telefone[MAX_NOME];
} Pessoa;

typedef struct {
    Livro livros[MAX_LIVROS];
    Pessoa dono;
} Estante;

#endif