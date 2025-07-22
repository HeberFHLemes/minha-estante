#include <stdio.h>
#include <string.h>
#include "../third_party/sqlite3/sqlite3.h"
#include "../include/estruturas.h"
#include "db_config.c"
#include "sql_ops.c"

#define SAIR 0

void mensagem_inicial();
int menu_opcoes(sqlite3 *db);
void direcionar_usuario(sqlite3 *db, int escolha);

void consultar_estante(sqlite3 *db);
void cadastrar_pessoa(sqlite3 *db);
void get_string(char* buffer, size_t tamanho_max, const char* frase);
int get_escolha_int(const char* frase);
void limpar_stdin();

int desconectar(sqlite3 *db);

int main(){

    mensagem_inicial();

    printf("Iniciando conexão ao banco de dados...\n");

    sqlite3 *db = NULL;
    if (conectar_db(&db, "minhaestante.db") != SQLITE_OK){
        return 1;
    }

    if (criar_tabelas(db) != 0){
        printf("Ocorreu um erro ao criar as tabelas para o banco de dados...\n");
        return desconectar(db);
    } else {
        printf("Banco de dados pronto!\n");
    }
    
    int escolha = menu_opcoes(db);
    while (escolha != SAIR){
        direcionar_usuario(db, escolha);
        escolha = menu_opcoes(db);
    }

    printf("Desconectando...\n");
    return desconectar(db);
}

int desconectar(sqlite3 *db){
    int rc = desconectar_db(db);
    if (rc == SQLITE_OK){
        printf("Desconectado com sucesso, até a próxima!\n");
    } else {
        printf("Erro ao desconectar do banco de dados.\n");
    }
    return rc;
}

void consultar_estante(sqlite3 *db){
    int pessoa_id = get_escolha_int("Digite o id do dono da estante a ser consultada: ");
    listar_estante(db, pessoa_id);
}

void cadastrar_pessoa(sqlite3 *db){
    
    char nome[MAX_NOME];
    get_string(nome, MAX_NOME, "Digite o nome: ");
    
    char telefone[MAX_NOME];
    get_string(telefone, MAX_NOME, "Digite o telefone para contato: ");

    inserir_pessoa(db, nome, telefone);
}

void direcionar_usuario(sqlite3 *db, int escolha){
    switch (escolha){
        case 1:
            cadastrar_pessoa(db);
            break;
        case 2:
            return;
        case 3:
            return;
        case 4:
            consultar_estante(db);
            break;
        case 5:
            return;
        case 6:
            return;
        case 7:
            return;
        case 8:
            return;
        default:
            return;
    }
}

void get_string(char* buffer, size_t tamanho_max, const char* frase){
    
    printf("%s", frase);
    fgets(buffer, tamanho_max, stdin);

    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }
}

// Limpa o stdin após scanf ou fgets
void limpar_stdin(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF); 
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

int menu_opcoes(sqlite3 *db){

    printf("+--------------------------+\n");
    printf("|      Menu de opções      |\n");
    printf("+--------------------------+\n");
    printf("| [1] - Cadastrar pessoa   |\n");
    printf("| [2] - Cadastrar livro    |\n");
    printf("| [3] - Consultar pessoa   |\n");
    printf("| [4] - Consultar estante  |\n");
    printf("| [5] - Atualizar pessoa   |\n");
    printf("| [6] - Remover pessoa     |\n");
    printf("| [7] - Atualizar livro    |\n");
    printf("| [8] - Remover livro      |\n");
    printf("| [0] - Sair               |\n");
    printf("+--------------------------+\n");
    return get_escolha_int("Digite sua escolha (0-8): ");
}

void mensagem_inicial(){

    printf("+============================================================================================================================+\n");
    printf("||                                                                                                                          ||\n");
    printf("||    |\\        /| | |\\    | |     |     /\\         ______   _____  _________     /\\     |\\    |  _________   ______        ||\n");
    printf("||    | \\      / | | | \\   | |     |    /  \\       |        |           |        /  \\    | \\   |      |      |              ||\n");
    printf("||    |  \\    /  | | |  \\  | |=====|   /----\\      |______  |_____      |       /----\\   |  \\  |      |      |______        ||\n");
    printf("||    |   \\  /   | | |   \\ | |     |  /      \\     |              |     |      /      \\  |   \\ |      |      |              ||\n");
    printf("||    |    \\/    | | |    \\| |     | /        \\    |______  ______|     |     /        \\ |    \\|      |      |______        ||\n");
    printf("||__________________________________________________________________________________________________________________________||\n");
    printf("\\____________________________________________________________________________________________________________________________/\n");

    printf("Iniciando programa...\n");
}