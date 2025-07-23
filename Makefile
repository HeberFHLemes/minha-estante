# gcc src/main.c src/leitor_sql.c src/console_utils.c src/db_config.c src/sql_ops.c src/user_interface.c -lsqlite3 -o MinhaEstante

# Compilador e flag utilizada 
CC = gcc
O_FLAG = -o

# Diretórios e arquivos utilizados
SRC_DIR = src
C_FILES = $(wildcard $(SRC_DIR)/*.c)
T_PARTY = -lsqlite3
EXE_NAME = MinhaEstante

# identifica que não serão arquivos
.PHONY: all build compile run clean

all: compile

build: compile

# compila como "gcc [arquivos .c] -lsqlite3 -o MinhaEstante"
compile:
	$(CC) $(C_FILES) $(T_PARTY) $(O_FLAG) $(EXE_NAME)

# executa o arquivo executável, se necessário fazendo o 'build' antes
run: build
	./$(EXE_NAME)

# Remove o arquivo executável
clean:
	rm -f $(EXE_NAME)