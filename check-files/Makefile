CC = gcc
CFLAGS = -Wall -Wextra -std=c99
LDFLAGS =

SRC_DIR = .
OBJ_DIR = ./output
BIN_DIR = ./output

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))
DEPS = $(wildcard $(SRC_DIR)/*.h)
EXEC = $(BIN_DIR)/main

.PHONY: all clean

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS) $(EXEC)
