CC = gcc
CFLAGS = -I ../ -std=c99 -ggdb -Wall
LDFLAGS = -lcunit
TEST = tests

SRC_TEST := $(wildcard *.c)
HDR_TEST := $(wildcard *.h);
OBJ_TEST = $(SRC_TEST:.c=.o)

ALL_SRCS := $(wildcard ../src/*.c)
SRC := $(filter-out ../src/main%.c, $(ALL_SRCS))
OBJ_SRC = $(SRC:.c=.o)

test:	$(OBJ_TEST) objsrc
	$(CC) $(CFLAGS) -o $(TEST) $(OBJ_TEST) $(OBJ_SRC) $(LDFLAGS)

objsrc:	
	$(MAKE) -C ../ gc

run_test: tests
	./$(TEST)

debug: test
	gdb ./$(TEST)

%.o: %.c %.h
	$(CC) $(CFLAGS) $*.c $*.h -c

%.o: %.c
	$(CC) $(CFLAGS) $< -c

valgrind: test
	valgrind --leak-check=yes ./$(TEST)

clean:
	rm -f $(OBJ_TEST) $(TEST) *~
	rm -f *#*
	rm -f *.gch

docs:
	doxygen Doxyfile

.PHONY = valgrind clean run