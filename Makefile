# Sintaxe - gcc: 
# 
# gerar sqlite3.o: (de: https://lloydrochester.com/post/c/add-sqlite-project/)
# - gcc -lpthread -ldl -o sqlite3.o -c third_party/sqlite3/sqlite3.c 
#
# gerar executável do projeto:
# - gcc -Iinclude -Ithird_party/sqlite3 -Wall -O2 -g -o bin/MinhaEstante src/main.c src/console_utils.c src/db_config.c src/leitor_sql.c src/sql_ops.c src/user_interface.c build/sqlite3.o

# Compilador e flags utilizadas 
CC = gcc

# Includes (include/ e thirdparty/sqlite3/)
INCLUDES = -Iinclude -Ithird_party/sqlite3

# Diretórios e arquivos utilizados
SRC_DIR = src
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
SQLITE_C = third_party/sqlite3/sqlite3.c
SQLITE_O = build/sqlite3.o # Compilado do sqlite3.c
EXE_NAME = bin/MinhaEstante # Gerado da compilação dos arquivos .c + sqlite3.o

# Uso dos includes + teste de outras flags
CFLAGS = $(INCLUDES) -Wall -O2 -g

# SQLite flags (warning na compilação do sqlite3.o -> variável setada mas não usada)
SQLITE_CFLAGS = $(CFLAGS) -Wno-unused-but-set-variable

# linkers para pthread e dl, pois o SQLite3 utiliza.
# LDFLAGS = -lpthread -ldl

# Checar a plataforma que está utilizando
UNAME_S := $(shell uname -s)

LDFLAGS =

ifeq ($(UNAME_S),Linux)
    LDFLAGS += -lpthread -ldl
endif

ifeq ($(OS),Windows_NT)
    # LDFLAGS += -lsqlite3 (if using prebuilt sqlite3.dll)
endif

# Opcional: caso utilize sqlite3.dll, por exemplo.
# T_PARTY_FLAG = -lsqlite3

# identifica que não serão arquivos
.PHONY: all build compile dirs run forget clean

all: compile

build: compile

# Compila, primeiro o sqlite3.c para sqlite3.o, depois o executável do projeto. (conferir sintaxe no topo deste arquivo)
compile: dirs
	$(CC) $(SQLITE_CFLAGS) -o $(SQLITE_O) -c $(SQLITE_C)
	$(CC) $(CFLAGS) -o $(EXE_NAME) $(SRC_FILES) $(SQLITE_O) $(LDFLAGS)

# Assegura que os diretórios build/ e bin/ existem
dirs:
	mkdir -p build bin

# executa o arquivo executável, se necessário fazendo o 'build' antes
run: build
	./$(EXE_NAME)

# remove o banco de dados (.db) e outros arquivos que estão no data/
forget: 
	rm -f data/*

# Remove o arquivo executável
clean:
	rm -f bin/* build/*