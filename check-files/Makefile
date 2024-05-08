CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRC_DIR = .
OBJ_DIR = ./output
EXEC = $(OBJ_DIR)/main

# Lista de archivos fuente
SRCS = $(wildcard $(SRC_DIR)/*.c)

# Generar nombres de archivos objeto
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Regla para construir el ejecutable
$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

# Regla para construir los archivos objeto
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Regla para limpiar los archivos generados
clean:
	rm -rf $(OBJ_DIR)/*.o $(EXEC)

# No confundir limpiar con un archivo llamado "clean"
.PHONY: clean
