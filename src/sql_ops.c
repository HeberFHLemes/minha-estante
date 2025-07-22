#include <stdio.h>
#include "../third_party/sqlite3/sqlite3.h"
#include "leitor_sql.c"
#include "../include/sql_ops.h"

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

int executarSTMT(sqlite3 *db, sqlite3_stmt* stmt){
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        fprintf(stderr, "Execução falhou: %s\n", sqlite3_errmsg(db));
        return SQLITE_ERROR;
    }
    return SQLITE_OK;
}

// INSERT
int inserirPessoa(sqlite3 *db, char* nome, char* telefone){

    const char* sql = "INSERT INTO pessoas(nome, telefone) VALUES(?, ?);";
    sqlite3_stmt* stmt;  
    int rc = SQLITE_OK;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, nome, -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 2, telefone, -1, SQLITE_TRANSIENT);
        
        if (executarSTMT(db, stmt) != SQLITE_OK){
            rc = SQLITE_ERROR;
        }
        sqlite3_finalize(stmt);  
    } else {
        fprintf(stderr, "Statement SQL falhou: %s\n", sqlite3_errmsg(db));
        rc = SQLITE_ERROR;
    }
    return rc;
}

int inserirLivro(sqlite3 *db, int dono_id, char* titulo, char* autor, int ano, int edicao){

    const char* sql = "INSERT INTO livros(titulo, autor, ano, edicao, dono_id) VALUES(?, ?, ?, ?, ?);";
    sqlite3_stmt* stmt;  
    int rc = SQLITE_OK;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, titulo, -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 2, autor, -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(stmt, 3, ano);
        sqlite3_bind_int(stmt, 4, edicao);
        sqlite3_bind_int(stmt, 5, dono_id);
        
        if (executarSTMT(db, stmt) != SQLITE_OK){
            rc = SQLITE_ERROR;
        }
        sqlite3_finalize(stmt);  
    } else {
        fprintf(stderr, "Statement SQL falhou: %s\n", sqlite3_errmsg(db));
        rc = SQLITE_ERROR;
    }
    return rc;
}

// SELECT
void listarPessoas(sqlite3 *db){

    const char* sql = "SELECT * FROM pessoas;";
    sqlite3_stmt* stmt;  

    int rc;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Erro ao preparar a consulta: %s\n", sqlite3_errmsg(db));
        return;
    }
    
    printf("+- Pessoas cadastradas -+\n");
    // printf(" id | nome | telefone\n");
    printf(" %-3s | %-20s | %-10s\n", "id", "nome", "telefone");
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        const unsigned char* nome = sqlite3_column_text(stmt, 1);
        const unsigned char* telefone = sqlite3_column_text(stmt, 2);

        printf(" %-3d | %-20s | %-10s\n", id, nome, telefone);
    }

     if (rc != SQLITE_DONE) {
        fprintf(stderr, "Erro durante a consulta: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_finalize(stmt);
    return; 
}

char* buscarPessoa(sqlite3 *db, int pessoa_id){

}

char* listarEstante(sqlite3 *db, int pessoa_id){

}

char* listarLivrosDeUmAutor(sqlite3 *db, int pessoa_id, char* autor){

}

// UPDATE
int atualizarNome(sqlite3 *db, int pessoa_id){

}
int atualizarTelefone(sqlite3 *db, int pessoa_id){

}

// DELETE
int removerLivro(sqlite3 *db, int pessoa_id, int livro_id){

}
int removerPessoa(sqlite3 *db, int pessoa_id){

}