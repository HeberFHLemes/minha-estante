#include <stdio.h>
#include <string.h>
#include "../third_party/sqlite3/sqlite3.h"
#include "../include/estruturas.h"
#include "db_config.c"
#include "sql_ops.c"

#define SAIR 0

// TODO: 
// mover funções de operações e fluxo de escolhas para arquivos próprios

// Interface / Fluxo de escolhas do usuário
void mensagem_inicial();
int menu_opcoes(sqlite3 *db);
void direcionar_usuario(sqlite3 *db, int escolha);

// Operações com BD
void cadastrar_pessoa(sqlite3 *db);
void cadastrar_livro(sqlite3 *db);
void consultar_pessoa(sqlite3 *db);
void consultar_estante(sqlite3 *db);
void atualizar_pessoa(sqlite3 *db);
void atualizar_nome_pessoa(sqlite3 *db);
void atualizar_telefone_pessoa(sqlite3 *db);
void remover_registro_pessoa(sqlite3 *db);

// Inputs
void get_string(char* buffer, size_t tamanho_max, const char* frase);
int get_escolha_int(const char* frase);
void limpar_stdin();

// Conexão
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

void cadastrar_pessoa(sqlite3 *db){
    printf(" === Cadastro de pessoa ===\n");
    
    char nome[MAX_NOME];
    get_string(nome, MAX_NOME, "Digite o nome: ");
    
    char telefone[MAX_NOME];
    get_string(telefone, MAX_NOME, "Digite o telefone para contato: ");

    inserir_pessoa(db, nome, telefone);
}

void cadastrar_livro(sqlite3 *db){
    printf(" === Cadastro de livro ===\n");
    
    char titulo[MAX_NOME];
    get_string(titulo, MAX_NOME, "Digite o titulo do livro: ");
    
    char autor[MAX_NOME];
    get_string(autor, MAX_NOME, "Digite o nome do autor do livro: ");

    int ano = get_escolha_int("Digite o ano de publicação do livro: ");

    int edicao = get_escolha_int("Digite o número da edição: ");

    int dono_id = get_escolha_int("Digite o id do dono do livro: ");

    inserir_livro(db, dono_id, titulo, autor, ano, edicao);
}

/* Atualmente chamando listar_pessoas(sqlite3 *db) direto
void listar_tabela_pessoas(sqlite3 *db){
    listar_pessoas(db);
}*/

void consultar_pessoa(sqlite3 *db){
    int pessoa_id = get_escolha_int("Digite o id da pessoa a ser consultada: ");
    buscar_pessoa(db, pessoa_id);
}

void consultar_estante(sqlite3 *db){
    int pessoa_id = get_escolha_int("Digite o id do dono da estante a ser consultada: ");
    listar_estante(db, pessoa_id);
}

void atualizar_pessoa(sqlite3 *db){
    printf("+--------------------------+\n");
    printf("|     Atualizar Pessoa     |\n");
    printf("+--------------------------+\n");
    printf("| [1] - Alterar nome       |\n");
    printf("| [2] - Alterar telefone   |\n");
    printf("| [0] - Voltar             |\n");
    printf("+--------------------------+\n");
    int escolha = get_escolha_int("Digite sua escolha (0-2): ");

    switch (escolha){
        case 1:
            atualizar_nome_pessoa(db);
            break;
        case 2:
            atualizar_telefone_pessoa(db);
        default:
            printf("Opção inválida, tente novamente.\n");
            return atualizar_pessoa(db);
    }
}

void atualizar_nome_pessoa(sqlite3 *db){

    printf(" === Atualizar nome ===\n");

    int id = get_escolha_int("Digite o id da pessoa (ou 0 para cancelar): ");
    if (id == 0){
        printf("Cancelando operação...\n");
        return;
    }

    char nome[MAX_NOME];
    get_string(nome, MAX_NOME, "Digite o nome: ");
    
    atualizar_nome(db, id, nome);
}

void atualizar_telefone_pessoa(sqlite3 *db){
    
    printf(" === Atualizar telefone ===\n");

    int id = get_escolha_int("Digite o id da pessoa (ou 0 para cancelar): ");
    if (id == 0){
        printf("Cancelando operação...\n");
        return;
    }

    char telefone[MAX_NOME];
    get_string(telefone, MAX_NOME, "Digite o telefone para contato: ");
    
    atualizar_telefone(db, id, telefone);
}

void remover_registro_pessoa(sqlite3 *db){
    return;
}


void direcionar_usuario(sqlite3 *db, int escolha){
    switch (escolha){
        case 1:
            cadastrar_pessoa(db);
            break;
        case 2:
            cadastrar_livro(db);
            break;
        case 3:
            listar_pessoas(db);
            break;
        case 4:
            consultar_pessoa(db);
            break;
        case 5:
            consultar_estante(db);
            break;
        case 6:
            atualizar_info_pessoa(db);
            break;
        case 7:
            remover_registro_pessoa(db);
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

// Limpa o stdin após scanf ou fgets
void limpar_stdin(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF); 
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

    printf("Iniciando programa...\n");
}