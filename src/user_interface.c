#include <stdio.h>
#include <string.h>
#include "../include/user_interface.h"
#include "../include/console_utils.h"

void mensagem_inicial(){

    printf("+==========================================================================================================================+\n");
    printf("||                                                                                                                        ||\n");
    printf("||    |\\        /| | |\\    | |     |     /\\         ______   _____  _________     /\\     |\\    |  _________   ______      ||\n");
    printf("||    | \\      / | | | \\   | |     |    /  \\       |        |           |        /  \\    | \\   |      |      |            ||\n");
    printf("||    |  \\    /  | | |  \\  | |=====|   /----\\      |______  |_____      |       /----\\   |  \\  |      |      |______      ||\n");
    printf("||    |   \\  /   | | |   \\ | |     |  /      \\     |              |     |      /      \\  |   \\ |      |      |            ||\n");
    printf("||    |    \\/    | | |    \\| |     | /        \\    |______  ______|     |     /        \\ |    \\|      |      |______      ||\n");
    printf("||________________________________________________________________________________________________________________________||\n");
    printf("\\_________________________________________________________________________________________________________________________/\n");
    printf("%120s\n", "Author: @HeberFHLemes");

    // printf("Iniciando programa...\n");
    efeito_carregando_curto("Iniciando programa");
}

int menu_opcoes(sqlite3 *db){

    printf("+--------------------------+\n");
    printf("|      Menu de opções      |\n");
    printf("+--------------------------+\n");
    printf("| [1] - Cadastrar pessoa   |\n");
    printf("| [2] - Cadastrar livro    |\n");
    printf("| [3] - Listar pessoas     |\n");
    printf("| [4] - Consultar pessoa   |\n");
    printf("| [5] - Consultar estante  |\n");
    printf("| [6] - Atualizar pessoa   |\n");
    printf("| [7] - Remover pessoa     |\n");
    printf("| [8] - Atualizar livro    |\n");
    printf("| [9] - Remover livro      |\n");
    printf("| [0] - Sair               |\n");
    printf("+--------------------------+\n");
    return get_escolha_int("Digite sua escolha (0-9): ");
}

void efeito_carregando(char* base){
    const char *dots[] = {".  ", ".. ", "..."};

    for (int i = 0; i < 6; i++) {
        printf("\r%s%s", base, dots[i % 3]);
        fflush(stdout);
        sleep_padrao();
    }
    printf("\n");
}

void efeito_carregando_curto(char* base){
    const char *dots[] = {".  ", ".. ", "..."};

    for (int i = 0; i < 3; i++) {
        printf("\r%s%s", base, dots[i % 3]);
        fflush(stdout);
        sleep_padrao();
    }
    printf("\n");
}

void get_string(char* buffer, size_t tamanho_max, const char* frase){
    
    printf("%s", frase);
    fgets(buffer, tamanho_max, stdin);

    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    } else {
        limpar_stdin();
    }
}

// Apresenta uma frase ao usuário e retorna um int digitado pelo mesmo
int get_escolha_int(const char* frase){
    int escolha = 0;
    int resultado;

    printf("%s", frase);
    resultado = scanf("%d", &escolha);
    limpar_stdin();

    // validação do input
    if (resultado != 1) {
        printf("Entrada inválida. Tente novamente.\n");
        return get_escolha_int(frase);
    }

    return escolha;
}