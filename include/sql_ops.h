#include "../third_party/sqlite3/sqlite3.h"
#ifndef SQL_OPS
#define SQL_OPS

// CREATE TABLE
int criarTabelas(sqlite3 *db);

// INSERT
int inserirPessoa(sqlite3 *db, char* nome, char* telefone);
int inserirLivro(sqlite3 *db, int pessoa_id, char* titulo, char* autor, int ano, int edicao);

// SELECT
void listarPessoas(sqlite3 *db);
void buscarPessoa(sqlite3 *db, int pessoa_id);
void listarEstante(sqlite3 *db, int pessoa_id);
void listarLivrosDeUmAutor(sqlite3 *db, int pessoa_id, char* autor);

// UPDATE
int atualizarNome(sqlite3 *db, int pessoa_id, char* nome);
int atualizarTelefone(sqlite3 *db, int pessoa_id, char* telefone);

// DELETE
int removerLivro(sqlite3 *db, int pessoa_id, int livro_id);
int removerPessoa(sqlite3 *db, int pessoa_id);

// EXECUTE STATEMENTS
int executarSTMT(sqlite3 *db, sqlite3_stmt* stmt);

#endif