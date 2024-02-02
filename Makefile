CC=gcc
CFLAGS=-Wall -O2
OBJ_DIR=objects
EXEC=main

all: $(EXEC)

main: $(OBJ_DIR)/main.o $(OBJ_DIR)/individu.o $(OBJ_DIR)/population.o
	$(CC) -o $@ $^

$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<