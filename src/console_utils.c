#include <stdio.h>
#include "../include/console_utils.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#define SONO 500

// Com constante SONO
void sleep_padrao() {
    #ifdef _WIN32
        Sleep(SONO); // Sleep é em milissegundos
    #else
        usleep(SONO * 1000);  // usleep é em microssegundos
    #endif
}

// Com parâmetro
void sleep_ms(int ms){
    #ifdef _WIN32
        Sleep(ms);
    #else
        usleep(ms * 1000);
    #endif
}

// Limpa o stdin após scanf ou fgets
void limpar_stdin(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF); 
}