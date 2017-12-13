CC = gcc
CFLAGS = -std=c99 -ggdb
NAME = gc
SRC = main.c gc.c
OBJ = main.o gc.o

full: main.c
	$(CC) $(CFLAGS) $(SRC) -o $(NAME)