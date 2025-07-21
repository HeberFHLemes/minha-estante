#include "../third_party/sqlite3/sqlite3.h"
#ifndef DB_CONFIG
#define DB_CONFIG

int conectarBD(sqlite3 **db, const char *nomeBD);
int desconectarBD(sqlite3 *db);

#endif