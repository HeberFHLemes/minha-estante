#include <stdio.h>
#include "../include/db_config.h"
#include "../third_party/sqlite3/sqlite3.h"

// tenta abrir/criar banco de dados
int conectarBD(sqlite3 **db, const char *nomeBD){    
    int rc = sqlite3_open(nomeBD, db);
    if (rc != SQLITE_OK) {
        if (db && *db) {
            fprintf(stderr, "Erro ao abrir banco de dados %s: %s\n", nomeBD, sqlite3_errmsg(*db));
            desconectarBD(*db);
        } else {
            fprintf(stderr, "Erro ao abrir banco de dados %s: mensagem indisponível\n", nomeBD);
        }
    }
    return rc;
}

// tenta desconectar do banco de dados
int desconectarBD(sqlite3 *db){
    if (db == NULL) return SQLITE_OK;
    int rc = sqlite3_close(db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Erro ao tentar fechar conexão com banco de dados: %s\n", sqlite3_errmsg(db));
    }
    return rc;
}