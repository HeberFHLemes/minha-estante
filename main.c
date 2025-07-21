#include <stdio.h>
#include <sqlite3.h>
#include "estruturas.h"

int conectarBD(sqlite3 **db, const char *nomeBD);
int desconectarBD(sqlite3 *db);

int main(){
    /* Pessoa p = {
        .nome = "Exemplo",
        .telefone = "1234-5678"
    };
    printf("%s", p.nome); */
    // database: "minhaestante.db"
    sqlite3 *db;

    if (conectarBD(&db, "minhaestante.db") != SQLITE_OK){
        fprintf(stderr, "Erro ao tentar abrir/criar base de dados: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    if (desconectarBD(db) != SQLITE_OK){
        fprintf(stderr, "Erro ao tentar fechar base de dados: %s\n", sqlite3_errmsg(db));
        return 1;
    }
    printf("Sucesso!");
    return 0;
}

// tenta abrir/criar banco de dados
int conectarBD(sqlite3 **db, const char *nomeBD){    
    return sqlite3_open("minhaestante.db", db);
}

// tenta desconectar do banco de dados
int desconectarBD(sqlite3 *db){
    return sqlite3_close(db);
}