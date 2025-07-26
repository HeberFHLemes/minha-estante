#ifndef USER_OPS_H
#define USER_OPS_H

#include "sqlite3.h"
#include "sql_ops.h"
#include "estruturas.h"

// Fluxo de escolhar do usuário + inputs -> direcionar para a função desejada
void direcionar_usuario(sqlite3 *db, int escolha);

// Operações com BD
void cadastrar_pessoa(sqlite3 *db);
void cadastrar_livro(sqlite3 *db);
void consultar_pessoa(sqlite3 *db);
void consultar_estante(sqlite3 *db);
void atualizar_pessoa(sqlite3 *db);
void atualizar_nome_pessoa(sqlite3 *db);
void atualizar_telefone_pessoa(sqlite3 *db);
void remover_registro_pessoa(sqlite3 *db);
void atualizar_livro(sqlite3 *db);
void remover_registro_livro(sqlite3 *db);

#endif