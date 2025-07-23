#ifndef DB_CONFIG_H
#define DB_CONFIG_H

#include "sqlite3.h"

extern const char* DB_PATH;
int conectar_db(sqlite3 **db);
int desconectar_db(sqlite3 *db);

#endif