#ifndef DB_CONFIG_H
#define DB_CONFIG_H

#include "sqlite3.h"

// Caminho/nome do banco de dados
#define DB_PATH "data/minhaestante.db"

int conectar_db(sqlite3 **db);
int desconectar_db(sqlite3 *db);

#endif