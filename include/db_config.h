#ifndef DB_CONFIG_H
#define DB_CONFIG_H

#include "sqlite3.h"

// Caminho/nome do banco de dados
extern const char* DB_PATH;
// #define DB_PATH "minhaestante.db"

int conectar_db(sqlite3 **db);
int desconectar_db(sqlite3 *db);

#endif