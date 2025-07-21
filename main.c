#include <stdio.h>
#include <sqlite3.h>
#include "estruturas.h"

int main(){
    Pessoa p = {
        .nome = "Exemplo",
        .telefone = "1234-5678"
    };
    printf("%s", p.nome);

    return 0;
}