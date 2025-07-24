#include <stdio.h>
#include "db_config.h"

// const char* DB_PATH = "minhaestante.db";

// tenta abrir/criar banco de dados
int conectar_db(sqlite3 **db){    

    int rc = sqlite3_open(DB_PATH, db);
    
    if (rc != SQLITE_OK) {
        if (db && *db) {
            fprintf(stderr, "Erro conectar com o banco de dados %s: %s\n", DB_PATH, sqlite3_errmsg(*db));
            desconectar_db(*db);
            *db = NULL;  // definir como nulo caso falhe
        } else {
            fprintf(stderr, "Erro ao conectar com o banco de dados %s: mensagem indisponível\n", DB_PATH);
        }
    }
    return rc;
}

// tenta desconectar do banco de dados
int desconectar_db(sqlite3 *db){

    if (db == NULL) return SQLITE_OK;
    
    int rc = sqlite3_close(db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Erro ao tentar fechar conexão com banco de dados: %s\n", sqlite3_errmsg(db));
    }
    return rc;
}