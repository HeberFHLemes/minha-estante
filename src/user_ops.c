#include <stdio.h>
#include <string.h>
#include "user_interface.h"
#include "user_ops.h"

// Fluxo de escolhar do usuário + inputs -> direcionar para a função desejada
void direcionar_usuario(sqlite3 *db, int escolha){
    switch (escolha){
        case 1:
            cadastrar_pessoa(db);
            break;
        case 2:
            cadastrar_livro(db);
            break;
        case 3:
            listar_pessoas(db);
            break;
        case 4:
            consultar_pessoa(db);
            break;
        case 5:
            consultar_estante(db);
            break;
        case 6:
            atualizar_pessoa(db);
            break;
        case 7:
            remover_registro_pessoa(db);
            break;
        case 8:
            atualizar_livro(db);
            break;
        case 9:
            remover_registro_livro(db);
            break;
        default:
            return;
    }
}

void cadastrar_pessoa(sqlite3 *db){
    printf(" === Cadastro de pessoa ===\n");
    
    char nome[MAX_NOME];
    get_string(nome, MAX_NOME, "Digite o nome: ");
    
    char telefone[MAX_NOME];
    get_string(telefone, MAX_NOME, "Digite o telefone para contato: ");

    // Uso do struct Pessoa (estruturas.h)
    Pessoa pessoa;
    strncpy(pessoa.nome, nome, MAX_NOME);
    pessoa.nome[MAX_NOME - 1] = '\0';

    strncpy(pessoa.telefone, telefone, MAX_NOME);
    pessoa.telefone[MAX_NOME - 1] = '\0';

    inserir_pessoa(db, &pessoa);
}

void cadastrar_livro(sqlite3 *db){
    printf(" === Cadastro de livro ===\n");
    
    char titulo[MAX_NOME];
    get_string(titulo, MAX_NOME, "Digite o titulo do livro: ");
    
    char autor[MAX_NOME];
    get_string(autor, MAX_NOME, "Digite o nome do autor do livro: ");

    int ano = get_escolha_int("Digite o ano de publicação do livro: ");

    int edicao = get_escolha_int("Digite o número da edição: ");

    int dono_id = get_escolha_int("Digite o id do dono do livro: ");

    // Uso do struct Livro (estruturas.h)
    Livro livro = { 
        .ano = ano,
        .edicao = edicao,
        .dono_id = dono_id
    };
    strncpy(livro.titulo, titulo, MAX_NOME);
    livro.titulo[MAX_NOME - 1] = '\0';

    strncpy(livro.autor, autor, MAX_NOME);
    livro.autor[MAX_NOME - 1] = '\0';
    
    inserir_livro(db, &livro);
}

void consultar_pessoa(sqlite3 *db){
    printf(" === Consultar pessoa ===\n");
    int pessoa_id = get_escolha_int("Digite o id da pessoa a ser consultada: ");
    buscar_pessoa(db, pessoa_id);
}

void consultar_estante(sqlite3 *db){
    int pessoa_id = get_escolha_int("Digite o id do dono da estante a ser consultada: ");
    listar_estante(db, pessoa_id);
}

void atualizar_pessoa(sqlite3 *db){
    printf("+--------------------------+\n");
    printf("|     Atualizar Pessoa     |\n");
    printf("+--------------------------+\n");
    printf("| [1] - Alterar nome       |\n");
    printf("| [2] - Alterar telefone   |\n");
    printf("| [0] - Voltar             |\n");
    printf("+--------------------------+\n");
    int escolha = get_escolha_int("Digite sua escolha (0-2): ");

    switch (escolha){
        case 1:
            atualizar_nome_pessoa(db);
            break;
        case 2:
            atualizar_telefone_pessoa(db);
            break;
        default:
            printf("Opção inválida, tente novamente.\n");
            return atualizar_pessoa(db);
    }
}

void atualizar_nome_pessoa(sqlite3 *db){

    printf(" === Atualizar nome ===\n");

    int id = get_escolha_int("Digite o id da pessoa (ou 0 para cancelar): ");
    if (id == 0){
        printf("Cancelando operação...\n");
        return;
    }

    char nome[MAX_NOME];
    get_string(nome, MAX_NOME, "Digite o nome: ");
    
    atualizar_nome(db, id, nome);
}

void atualizar_telefone_pessoa(sqlite3 *db){
    
    printf(" === Atualizar telefone ===\n");

    int id = get_escolha_int("Digite o id da pessoa (ou 0 para cancelar): ");
    if (id == 0){
        printf("Operação cancelada.\n");
        return;
    }

    char telefone[MAX_NOME];
    get_string(telefone, MAX_NOME, "Digite o telefone para contato: ");
    
    atualizar_telefone(db, id, telefone);
}

void remover_registro_pessoa(sqlite3 *db){
    
    printf(" === Remover pessoa ===\n");  
    int id = get_escolha_int("Digite o id da pessoa (ou 0 para cancelar): ");
    if (id == 0){
        printf("Operação cancelada.\n");
        return;
    }
    remover_pessoa(db, id);
}

void atualizar_livro(sqlite3 *db){
    printf(" === Atualizar título de um livro ===\n");
    int id = get_escolha_int("Digite o id do livro (ou 0 para cancelar): ");
    if (id == 0){
        printf("Operação cancelada.\n");
        return;
    }    
    char titulo[MAX_NOME];
    get_string(titulo, MAX_NOME, "Digite o titulo do livro: ");

    atualizar_titulo(db, id, titulo);
}

void remover_registro_livro(sqlite3 *db){
    
    printf(" === Remover livro ===\n");
    int id = get_escolha_int("Digite o id do livro (ou 0 para cancelar): ");
    if (id == 0){
        printf("Operação cancelada.\n");
        return;
    }
    remover_livro(db, id);
}