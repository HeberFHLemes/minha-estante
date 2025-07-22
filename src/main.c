#include <stdio.h>
#include "../third_party/sqlite3/sqlite3.h"
#include "../include/estruturas.h"
#include "db_config.c"
#include "sql_ops.c"

#define SAIR 0

void mensagemInicial();
int direcionarUsuario(sqlite3 *db);
int desconectar(sqlite3 *db);

int main(){

    mensagemInicial();

    printf("Iniciando conexão ao banco de dados...\n");

    sqlite3 *db = NULL;
    if (conectarBD(&db, "minhaestante.db") != SQLITE_OK){
        return 1;
    }

    if (criarTabelas(db) != 0){
        printf("Ocorreu um erro ao criar as tabelas para o banco de dados...\n");
        return desconectar(db);
    } else {
        printf("Banco de dados pronto!\n");
    }

    int escolhaMenu = direcionarUsuario(db);
    while (escolhaMenu != SAIR){
        escolhaMenu = direcionarUsuario(db);
    }

    printf("Desconectando...\n");
    return desconectar(db);
}

int direcionarUsuario(sqlite3 *db){

    printf("+--------------------------+\n");
    printf("|      Menu de opções      |\n");
    printf("+--------------------------+\n");
    printf("| [1] - Cadastrar pessoa   |\n");
    printf("| [2] - Cadastrar livro    |\n");
    printf("| [3] - Consultar pessoa   |\n");
    printf("| [4] - Consultar estante  |\n");
    printf("| [5] - Atualizar pessoa   |\n");
    printf("| [6] - Remover pessoa     |\n");
    printf("| [7] - Atualizar livro    |\n");
    printf("| [8] - Remover livro      |\n");
    printf("| [0] - Sair               |\n");
    printf("+--------------------------+\n");
    int op = 0;
    scanf("%d", &op);
    return op;
}

int desconectar(sqlite3 *db){
    int rc = desconectarBD(db);
    if (rc == SQLITE_OK){
        printf("Desconectado com sucesso, até a próxima!\n");
    } else {
        printf("Erro ao desconectar do banco de dados.\n");
    }
    return rc;
}

void mensagemInicial(){

    printf("+============================================================================================================================+\n");
    printf("||                                                                                                                          ||\n");
    printf("||    |\\        /| | |\\    | |     |     /\\         ______   _____  _________     /\\     |\\    |  _________   ______        ||\n");
    printf("||    | \\      / | | | \\   | |     |    /  \\       |        |           |        /  \\    | \\   |      |      |              ||\n");
    printf("||    |  \\    /  | | |  \\  | |=====|   /----\\      |______  |_____      |       /----\\   |  \\  |      |      |______        ||\n");
    printf("||    |   \\  /   | | |   \\ | |     |  /      \\     |              |     |      /      \\  |   \\ |      |      |              ||\n");
    printf("||    |    \\/    | | |    \\| |     | /        \\    |______  ______|     |     /        \\ |    \\|      |      |______        ||\n");
    printf("||__________________________________________________________________________________________________________________________||\n");
    printf("\\____________________________________________________________________________________________________________________________/\n");

    printf("Iniciando programa...\n");
}