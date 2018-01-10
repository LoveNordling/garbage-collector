CC = gcc
CFLAGS = -std=c99 -ggdb -Wall
LDFLAGS = 
NAME = gc

SRC := $(wildcard *.c)
HDR := $(wildcard *.h);
OBJ = $(SRC:.c=.o)

all: gc test

gc: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LDFLAGS)

run: gc
	./$(NAME)

debug: gc
	gdb ./$(NAME)

%.o: %.c %.h
	$(CC) $(CFLAGS) $*.c $*.h -c

%.o: %.c
	$(CC) $(CFLAGS) $< -c

valgrind: all
	valgrind --leak-check=yes ./$(NAME)

clean:
	rm -f $(OBJ) $(NAME) *~
	rm -f *#*
	rm -f *.gch

docs:
	doxygen Doxyfile

.PHONY = valgrind clean run run_test
