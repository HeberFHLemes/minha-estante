#include <stdio.h>
#include "../third_party/sqlite3/sqlite3.h"
#include "../include/estruturas.h"
#include "db_config.c"
#include "leitor_sql.c"

int criarTabelas(sqlite3 *db);

int main(){
    sqlite3 *db = NULL;

    if (conectarBD(&db, "minhaestante.db") != SQLITE_OK){
        return 1;
    }

    if (criarTabelas(db) != 0){
        printf("Ocorreu um erro ao criar as tabelas...");
    }
    
    if (desconectarBD(db) != SQLITE_OK){
        return 1;
    }

    return 0;
}

int criarTabelas(sqlite3 *db){
    char* errMsg = NULL;
    char* sql = ler_sql("sql/tabelas.sql");
    if (!sql) {
        printf("Erro ao ler arquivo SQL.\n");
        return 1;
    }
    int rc = sqlite3_exec(db, sql, NULL, NULL, &errMsg);
    
    if (rc != SQLITE_OK){
        printf(sql);
        fprintf(stderr, "Erro SQLite (código %d): %s\n", rc, errMsg ? errMsg : "sem mensagem", errMsg);
        sqlite3_free(errMsg);
        return 2;
    } 
    free(sql); 
    return 0;
}