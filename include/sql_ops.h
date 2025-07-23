#ifndef SQL_OPS_H
#define SQL_OPS_H

#include "../third_party/sqlite3/sqlite3.h"
#include "estruturas.h"

// CREATE TABLE
int criar_tabelas(sqlite3 *db);

// INSERT
int inserir_pessoa(sqlite3 *db, Pessoa* pessoa);
int inserir_livro(sqlite3 *db, Livro* livro);

// SELECT
void listar_pessoas(sqlite3 *db);
void buscar_pessoa(sqlite3 *db, int pessoa_id);
void listar_estante(sqlite3 *db, int pessoa_id);
void listar_livros_de_autor(sqlite3 *db, int pessoa_id, char* autor);

// UPDATE
int atualizar_nome(sqlite3 *db, int pessoa_id, char* nome);
int atualizar_telefone(sqlite3 *db, int pessoa_id, char* telefone);

// DELETE
int remover_livro(sqlite3 *db, int pessoa_id, int livro_id);
int remover_pessoa(sqlite3 *db, int pessoa_id);

// EXECUTE STATEMENTS
int executar_stmt(sqlite3 *db, sqlite3_stmt* stmt);

#endif