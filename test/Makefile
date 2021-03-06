CC = gcc
CFLAGS = -I ../ -std=c99 -ggdb -Wall -fprofile-arcs -ftest-coverage -lgcov -pg -no-pie
LDFLAGS = -lcunit -fprofile-arcs -ftest-coverage -lgcov -pg -no-pie
TEST = tests

SRC_TEST := $(wildcard *.c)
HDR_TEST := $(wildcard *.h);
OBJ_TEST = $(SRC_TEST:.c=.o)

ALL_SRCS := $(wildcard ../src/*.c)
SRC := $(filter-out ../src/main%.c, $(ALL_SRCS))
OBJ_SRC = $(SRC:.c=.o)

all:	$(OBJ_TEST) objsrc
	$(CC) $(CFLAGS) -o $(TEST) $(OBJ_TEST) $(OBJ_SRC) $(LDFLAGS)

objsrc:	
	$(MAKE) -C ../src all

run: all
	./$(TEST)

debug: all
	gdb ./$(TEST)

%.o: %.c %.h
	$(CC) $(CFLAGS) $*.c $*.h -c

%.o: %.c
	$(CC) $(CFLAGS) $< -c

valgrind: all
	valgrind --leak-check=yes ./$(TEST)

clean:
	rm -f $(OBJ_TEST) $(TEST) *~
	rm -f *#*
	rm -f *.gch
	rm -f *.gcno
	rm -f *.gcda

docs:
	doxygen Doxyfile

.PHONY : valgrind clean run
