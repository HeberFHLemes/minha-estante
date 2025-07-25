# Sintaxe - gcc: 
# --------------
# gerar sqlite3.o:
# - gcc -Iinclude -Ilib/sqlite3 -Wall -O2 -g -Wno-unused-but-set-variable -c sqlite3.c -o sqlite3.o
# (linkagem para pthread e dl feita depois, no caso de não ser executado em ambiente Windows)
#
# gerar executável do projeto:
# - gcc -Iinclude -Ilib/sqlite3 -Wall -O2 -g -o MinhaEstante.exe [SRC_OBJS] sqlite3.o [opcional, dependendo de onde executa: -lpthread -ldl]
# (SRC_OBJS: Arquivos como src/exemplo.c transformados em build/exemplo.o)

# Compilador e flags utilizadas 
CC = gcc

# Includes (include/ e lib/sqlite3/)
INCLUDES = -Iinclude -Ilib/sqlite3

# Diretórios e arquivos utilizados
SRC_DIR = src
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_DIR = build
BIN_DIR = bin
EXE_NAME = $(BIN_DIR)/MinhaEstante

SQLITE_C = lib/sqlite3/sqlite3.c

# Compilado do sqlite3.c
SQLITE_O = $(OBJ_DIR)/sqlite3.o

# Uso dos includes + teste de outras flags
CFLAGS = $(INCLUDES) -Wall -O2 -g

# SQLite flags (warning na compilação do sqlite3.o -> variável setada mas não usada)
SQLITE_CFLAGS = $(CFLAGS) -Wno-unused-but-set-variable

# --- linkers para pthread e dl, pois o SQLite3 utiliza: ---
# 1. Checar a plataforma que está utilizando
UNAME_S := $(shell uname -s)

# 2. atribuir conforme ambiente que executa
LDFLAGS =
ifeq ($(UNAME_S),Linux)
    LDFLAGS += -lpthread -ldl
endif

# Opcional: caso utilize sqlite3.dll, por exemplo.
# T_PARTY_FLAG = -lsqlite3
# ifeq ($(OS),Windows_NT)
    # LDFLAGS += $(T_PARTY_FLAG)
# endif
# ---

# Listar os arquivos .o vindos de src/*.c e pôr no build/ ("substituição com padrão")
SRC_OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))

# identifica que não serão arquivos
.PHONY: all clean run dirs rebuild

# Requer o .exe
all: $(EXE_NAME)

# .exe: requer os objetos de src/*.c, o .o de sqlite3.c e a existência dos diretórios citados em dirs
# Compila com: gcc -Iinclude -Ilib/sqlite3 -Wall -O2 -g -o MinhaEstante.exe [SRC_OBJS] sqlite3.o [se em Linux: -lpthread -ldl]
$(EXE_NAME): $(SRC_OBJS) $(SQLITE_O) | dirs
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Compila o sqlite3.c para sqlite3.o
# Compila com: gcc -Iinclude -Ilib/sqlite3 -Wall -O2 -g -Wno-unused-but-set-variable -c sqlite3.c -o sqlite3.o
$(SQLITE_O): $(SQLITE_C) | dirs
	$(CC) $(SQLITE_CFLAGS) -c $< -o $@

# Compila cada src/[].c para build/[].o
# Compila com: gcc [CFLAGS] -c [src/*.c]  [build/*.o]
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | dirs
	$(CC) $(CFLAGS) -c $< -o $@

# Assegura que os diretórios build/ e bin/ existem
dirs:
	mkdir -p build bin data

# executa o arquivo executável, se necessário fazendo o 'build' antes
run: $(EXE_NAME)
	./$(EXE_NAME)

# Remove o arquivo executável e os arquivos .o
clean:
	rm -r $(BIN_DIR)/* $(OBJ_DIR)/*

# Apenas por manter
build: all

# Chama o clean e reconstrói
rebuild: clean all

# remove o banco de dados (.db) e outros arquivos que estão no data/
forget: 
	rm -f data/*

# - Compilação foi atualizada, esta compilava tudo toda vez -
# Compila, primeiro o sqlite3.c para sqlite3.o, depois o executável do projeto. (conferir sintaxe no topo deste arquivo)
# compile: dirs
# 	$(CC) $(SQLITE_CFLAGS) -o $(SQLITE_O) -c $(SQLITE_C)
# 	$(CC) $(CFLAGS) -o $(EXE_NAME) $(SRC_FILES) $(SQLITE_O) $(LDFLAGS)
# ---