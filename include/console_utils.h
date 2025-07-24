#ifndef CONSOLE_UTILS_H
#define CONSOLE_UTILS_H

#define ANSI_RESET "\x1b[0m"
#define ANSI_GREEN "\x1b[32m"

void sleep_padrao();
void sleep_ms(int ms);
void limpar_stdin();

#endif