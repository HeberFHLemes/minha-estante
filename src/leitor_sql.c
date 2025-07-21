#include "../include/leitor_sql.h"
#include <stdio.h>
#include <stdlib.h>

// Para ler o arquivo .sql e retornar o conteúdo a ser executado
char* ler_sql(const char* arquivo){
    FILE* arq = fopen(arquivo, "rb");
    if (!arq){
        printf("Erro ao abrir arquivo...");
        return NULL;
    } 

    // Semelhante a manipulação de ResultSet em Java (mover o cursor)
    fseek(arq, 0, SEEK_END);
    long tamanho = ftell(arq);
    fseek(arq, 0, SEEK_SET);

    if (tamanho <= 0) {
        fclose(arq);
        fprintf(stderr, "Arquivo está vazio ou houve erro ao determinar o tamanho.\n");
        return NULL;
    }

    char* buffer = malloc(tamanho + 1); // tamanho + 1 para o '\0'
    if (!buffer) {
        fclose(arq);
        fprintf(stderr, "Erro ao alocar memória para leitura do arquivo.\n");
        return NULL; // ! - Possível retorno de NULL
    }

    size_t lidos = fread(buffer, 1, tamanho, arq);
    if (lidos != tamanho) {
        fprintf(stderr, "Erro durante leitura do arquivo. Lidos %zu bytes, esperados %ld.\n", lidos, tamanho);
        free(buffer);
        fclose(arq);
        return NULL;
    }
    buffer[tamanho] = '\0'; // !!! - Para 'ser' string
    fclose(arq);
    return buffer;
}