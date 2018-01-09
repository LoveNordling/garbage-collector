CC = gcc
CFLAGS = -std=c99 -ggdb -Wall  -fprofile-arcs -ftest-coverage -lgcov -pg -no-pie 
LDFLAGS = -fprofile-arcs -ftest-coverage -lgcov -pg -no-pie
NAME = gc

SRC := $(wildcard *.c)
HDR := $(wildcard *.h);
OBJ = $(SRC:.c=.o)

all: gc test

gc: $(OBJ)
	$(CC) $(LDFLAGS) $(OBJ) -o $(NAME) 



run: gc
	./$(NAME)

test:
	$(MAKE) -C tests test

run_test: test
	$(MAKE) -C tests run_test


debug: gc
	gdb ./gc

debug_test: test
	$(MAKE) -C tests debug	


%.o: %.c %.h
	$(CC) $(CFLAGS) $*.c $*.h -c

%.o: %.c
	$(CC) $(CFLAGS) $< -c

valgrind: all
	valgrind --leak-check=yes ./$(NAME)

clean:
	rm -f $(OBJ) $(NAME) *~
	$(MAKE) -C tests clean
	rm -f *#
	rm -f *.gch
	rm -f *.gcno
	rm -f *.gcda

docs:
	doxygen Doxyfile

.PHONY = valgrind clean run run_test
