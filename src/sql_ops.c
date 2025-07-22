#include <stdio.h>
#include "../third_party/sqlite3/sqlite3.h"
#include "leitor_sql.c"
#include "../include/sql_ops.h"

// Cria as tabelas (se ainda não existirem) com o arquivo .sql citado
int criar_tabelas(sqlite3 *db){

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

// Executa um statement preparado (como sqlite3_prepare_v2(db, sql, -1, &stmt, NULL)).
int executar_stmt(sqlite3 *db, sqlite3_stmt* stmt){
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        fprintf(stderr, "Execução falhou: %s\n", sqlite3_errmsg(db));
        return SQLITE_ERROR;
    }
    return SQLITE_OK;
}

// INSERT
// Insere nova pessoa na tabela de pessoas
int inserir_pessoa(sqlite3 *db, char* nome, char* telefone){

    const char* sql = "INSERT INTO pessoas(nome, telefone) VALUES(?, ?);";
    sqlite3_stmt* stmt;  
    int rc = SQLITE_OK;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, nome, -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 2, telefone, -1, SQLITE_TRANSIENT);
        
        if (executar_stmt(db, stmt) != SQLITE_OK){
            rc = SQLITE_ERROR;
        }
        sqlite3_finalize(stmt);  
    } else {
        fprintf(stderr, "Statement SQL falhou: %s\n", sqlite3_errmsg(db));
        rc = SQLITE_ERROR;
    }
    return rc;
}

// Insere novo livro na tabela livros
int inserir_livro(sqlite3 *db, int dono_id, char* titulo, char* autor, int ano, int edicao){

    const char* sql = "INSERT INTO livros(titulo, autor, ano, edicao, dono_id) VALUES(?, ?, ?, ?, ?);";
    sqlite3_stmt* stmt;  
    int rc = SQLITE_OK;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, titulo, -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 2, autor, -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(stmt, 3, ano);
        sqlite3_bind_int(stmt, 4, edicao);
        sqlite3_bind_int(stmt, 5, dono_id);
        
        if (executar_stmt(db, stmt) != SQLITE_OK){
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
// Lista todas as colunas de todas as linha da tabela de pessoas
void listar_pessoas(sqlite3 *db){

    const char* sql = "SELECT * FROM pessoas;";
    sqlite3_stmt* stmt;  

    int rc;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Erro ao preparar a consulta: %s\n", sqlite3_errmsg(db));
        return;
    }
    
    printf("+- Pessoas cadastradas -+\n");
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

// Tenta encontrar uma pessoa com um id específico
void buscar_pessoa(sqlite3 *db, int pessoa_id){

    const char* sql = "SELECT * FROM pessoas WHERE id = ?;";
    sqlite3_stmt* stmt;  

    int rc;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Erro ao preparar a consulta: %s\n", sqlite3_errmsg(db));
        return;
    }
    sqlite3_bind_int(stmt, 1, pessoa_id);

    printf("+- Consulta de pessoa cadastrada -+\n");
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

// Lista todos os livros de uma pessoa com id 'pessoa_id', logo, sua 'estante'
void listar_estante(sqlite3 *db, int pessoa_id){

    const char* sql = "SELECT l.*, p.nome, p.telefone FROM livros l RIGHT JOIN pessoas p ON l.dono_id = p.id WHERE l.dono_id = ?;";
    sqlite3_stmt* stmt; 

    int rc;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Erro ao preparar a consulta: %s\n", sqlite3_errmsg(db));
        return;
    }
    sqlite3_bind_int(stmt, 1, pessoa_id);

    printf("\n=====  Consulta de estante =====\n");
    printf("+-----+-----------------+------------+------+--------+---------+-----------------+-----------------+\n");
    printf("| %-3s | %-15s | %-10s | %-4s | %-6s | %-7s | %-15s | %-15s |\n", "id", "titulo", "autor", "ano", "edicao", "dono_id", "nome", "contato");
    printf("+-----+-----------------+------------+------+--------+---------+-----------------+-----------------+\n");
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        
        int id = sqlite3_column_int(stmt, 0);
        const unsigned char* titulo = sqlite3_column_text(stmt, 1);
        const unsigned char* autor = sqlite3_column_text(stmt, 2);
        int ano = sqlite3_column_int(stmt, 3);
        int edicao = sqlite3_column_int(stmt, 4);
        int dono_id = sqlite3_column_int(stmt, 5);
        const unsigned char* nome = sqlite3_column_text(stmt, 6);
        const unsigned char* telefone = sqlite3_column_text(stmt, 7);

        printf("| %-3d | %-15s | %-10s | %-4d | %-6d | %-7d | %-15s | %-10s |\n", id, titulo, autor, ano, edicao, dono_id, nome, telefone);
    }

    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Erro durante a consulta: %s\n", sqlite3_errmsg(db));
    } else {
        printf("+-----+-----------------+------------+------+--------+---------+-----------------+-----------------+\n");
    }

    sqlite3_finalize(stmt);
    return; 
}

// Lista todos os livros de uma pessoa específica escritos por um autor específico
void listar_livros_de_autor(sqlite3 *db, int pessoa_id, char* autor){
    const char* sql = "SELECT * FROM livros WHERE dono_id = ? AND autor = ?";
    sqlite3_stmt* stmt; 

    int rc;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Erro ao preparar a consulta: %s\n", sqlite3_errmsg(db));
        return;
    }
    sqlite3_bind_int(stmt, 1, pessoa_id);
    sqlite3_bind_text(stmt, 2, autor, -1, SQLITE_TRANSIENT);

    printf("\n=====  Consulta - livros escritos por %s na estante =====\n", autor);
    printf("+-----+-----------------+------------+------+--------+---------+\n");
    printf("| %-3s | %-15s | %-10s | %-4s | %-6s | %-7s |\n", "id", "titulo", "autor", "ano", "edicao", "dono_id");
    printf("+-----+-----------------+------------+------+--------+---------+\n");
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        
        int id = sqlite3_column_int(stmt, 0);
        const unsigned char* titulo = sqlite3_column_text(stmt, 1);
        const unsigned char* autor = sqlite3_column_text(stmt, 2);
        int ano = sqlite3_column_int(stmt, 3);
        int edicao = sqlite3_column_int(stmt, 4);
        int dono_id = sqlite3_column_int(stmt, 5);

        printf("| %-3d | %-15s | %-10s | %-4d | %-6d | %-7d |\n", id, titulo, autor, ano, edicao, dono_id);
    }

    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Erro durante a consulta: %s\n", sqlite3_errmsg(db));
    } else {
        printf("+-----+-----------------+------------+------+--------+---------+\n");
    }

    sqlite3_finalize(stmt);
    return; 
}

// UPDATE
int atualizar_nome(sqlite3 *db, int pessoa_id, char* nome){
    const char* sql = "UPDATE pessoas SET nome = ? WHERE id = ?";
    sqlite3_stmt* stmt; 

    int rc = SQLITE_OK;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, pessoa_id);
        sqlite3_bind_text(stmt, 2, nome, -1, SQLITE_TRANSIENT);
        
        if (executar_stmt(db, stmt) != SQLITE_OK){
            rc = SQLITE_ERROR;
        }
        sqlite3_finalize(stmt);  
    } else {
        fprintf(stderr, "Statement SQL falhou: %s\n", sqlite3_errmsg(db));
        rc = SQLITE_ERROR;
    }
    return rc;
}

int atualizar_telefone(sqlite3 *db, int pessoa_id, char* telefone){
    const char* sql = "UPDATE pessoas SET telefone = ? WHERE id = ?";
    sqlite3_stmt* stmt; 

    int rc = SQLITE_OK;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, pessoa_id);
        sqlite3_bind_text(stmt, 2, telefone, -1, SQLITE_TRANSIENT);
        
        if (executar_stmt(db, stmt) != SQLITE_OK){
            rc = SQLITE_ERROR;
        }
        sqlite3_finalize(stmt);  
    } else {
        fprintf(stderr, "Statement SQL falhou: %s\n", sqlite3_errmsg(db));
        rc = SQLITE_ERROR;
    }
    return rc;
}

// DELETE
int remover_livro(sqlite3 *db, int pessoa_id, int livro_id){

}
int remover_pessoa(sqlite3 *db, int pessoa_id){

}