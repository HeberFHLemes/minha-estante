#include "../third_party/sqlite3/sqlite3.h"

// Interface / Fluxo de escolhas do usuário
void mensagem_inicial();
int menu_opcoes(sqlite3 *db);
void efeito_carregando(char* base);

// Inputs/entradas do usuário
void get_string(char* buffer, size_t tamanho_max, const char* frase);
int get_escolha_int(const char* frase);