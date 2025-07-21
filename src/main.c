#include <stdio.h>
#include "../third_party/sqlite3/sqlite3.h"
#include "../include/estruturas.h"
#include "db_config.c"
#include "sql_ops.c"

int main(){

    printf("Iniciando programa...\n");
    printf("Tentando conectar ao banco de dados...\n");

    sqlite3 *db = NULL;
    if (conectarBD(&db, "minhaestante.db") != SQLITE_OK){
        return 1;
    }

    if (criarTabelas(db) != 0){
        printf("Ocorreu um erro ao criar as tabelas para o banco de dados...\n");
    } else {
        printf("Banco de dados pronto!\n");
    }

    printf("Pressione ENTER para sair:");
    getchar();

    printf("Desconectando...\n");
    if (desconectarBD(db) != SQLITE_OK){
        return 1;
    }
    printf("Desconectado com sucesso, até a próxima!\n");

    return 0;
}