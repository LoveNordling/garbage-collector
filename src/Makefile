CC = gcc
CFLAGS = -std=c99 -ggdb -Wall -fprofile-arcs -ftest-coverage -lgcov -pg -no-pie
LDFLAGS = -fprofile-arcs -ftest-coverage -lgcov -pg -no-pie 
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
	rm -f *.gcda
	rm -f *.gcno

docs:
	doxygen Doxyfile

.PHONY = valgrind clean run run_test
