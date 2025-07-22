#include "../third_party/sqlite3/sqlite3.h"
#ifndef DB_CONFIG
#define DB_CONFIG

int conectar_db(sqlite3 **db, const char *nomeBD);
int desconectar_db(sqlite3 *db);

#endif