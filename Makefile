CC = gcc
CFLAGS = -std=c99 -ggdb -Wall
NAME = gc

SRC := $(wildcard *.c)
HDR := $(wildcard *.h);
OBJ = $(SRC:.c=.o)
SRCTEST := $(wildcard test/*.c)
HDRTEST := $(wildcard test/*.h)
OBJTEST = $(SRCTEST:.c=.o)

all: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) 

%.o: %.c %.h
	$(CC) $(CFLAGS) $*.c $*.h -c

%.o: %.c
	$(CC) $(CFLAGS) $< -c

run: all
	./$(NAME)

cleanrun: 
	make clean
	make run

run_test: test
	./test

test: test_main test_root
	$(CC) $(CFLAGS) $(OBJ) $(OBJTEST) -lcunit -o test


test_main: $(OBJ)
	$(CC) $(CFLAGS) "tests/test.c" -lcunit -c


test_root: $(OBJ)
	$(CC) $(CFLAGS) "tests/test_root.c" -lcunit -c

valgrind: all
	valgrind --leak-check=yes ./$(NAME)

clean:
	rm -f *.o
	rm -f *~
	rm -f *#
	rm -f *.*.*
	rm -f gc

docs:
	doxygen Doxyfile

.PHONY = valgrind clean run
