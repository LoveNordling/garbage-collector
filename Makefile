CC = gcc
CFLAGS = -std=c99 -ggdb
NAME = gc

SRC := $(wildcard *.c)
HDR := $(wildcard *.h);
OBJ = $(SRC:.c=.o)

full: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c %.h
	$(CC) $(CFLAGS) $*.c $*.h -c

%.o: %.c
	$(CC) $(CFLAGS) $< -c

run: full
	./$(NAME)

valgrind: full
	valgrind --leak-check=yes ./$(NAME)

clean:
	rm -f *.o
	rm -f *~
	rm -f *# 

.PHONY = valgrind clean run
