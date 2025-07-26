#include <stdio.h>
#include "db_config.h"
#include "sql_ops.h"
#include "user_interface.h"
#include "console_utils.h"
#include "user_ops.h"

#define SAIR 0

int desconectar(sqlite3 *db);

int main(){

    mensagem_inicial();

    efeito_carregando("Iniciando conexão com o banco de dados");
    
    sqlite3 *db = NULL;
    if (conectar_db(&db) != SQLITE_OK) return 1;

    if (criar_tabelas(db) != 0){
        printf("Ocorreu um erro ao criar as tabelas para o banco de dados...\n");
        return desconectar(db);
    } else {
        printf(ANSI_GREEN "Banco de dados pronto e conexão efetuada!\n" ANSI_RESET);
    }
    printf("Seja bem-vindo!\n");
    
    int escolha = menu_opcoes(db);
    while (escolha != SAIR){
        direcionar_usuario(db, escolha);
        escolha = menu_opcoes(db);
    }

    efeito_carregando("Desconectando");
    return desconectar(db);
}

// Chama desconectar_db(), mas com output para o usuário.
int desconectar(sqlite3 *db){
    int rc = desconectar_db(db);
    if (rc == SQLITE_OK){
        printf("Desconectado com sucesso, até a próxima!\n");
    } else {
        printf("Erro ao desconectar do banco de dados.\n");
    }
    return rc;
}