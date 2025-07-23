#include <stdio.h>
#include "../include/db_config.h"
#include "../third_party/sqlite3/sqlite3.h"

// tenta abrir/criar banco de dados
int conectar_db(sqlite3 **db, const char *nome_db){    

    int rc = sqlite3_open(nome_db, db);
    
    if (rc != SQLITE_OK) {
        if (db && *db) {
            fprintf(stderr, "Erro conectar com o banco de dados %s: %s\n", nome_db, sqlite3_errmsg(*db));
            desconectar_db(*db);
        } else {
            fprintf(stderr, "Erro ao conectar com o banco de dados %s: mensagem indisponível\n", nome_db);
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