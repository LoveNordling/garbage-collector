tests/%.o: tests/%.c tests/%.h
	$(CC) $(CFLAGS) tests/$*.c tests/$*.h -c -lcunit


tests/%.o: tests/%.c
	$(CC) $(CFLAGS) tests/$< -c -lcunittests/CC = gcc
CFLAGS = -std=c99 -ggdb -Wall
NAME = gc

SRC := $(wildcard *.c)
HDR := $(wildcard *.h);
OBJ = $(SRC:.c=.o)

#TODO FIX THESE (Do tests need .o files? Dunno I don't know cunit)
SRC_TEST := $(wildcard tests/*.c)
HDR_TEST := $(wildcard tests/*.h);
OBJ_TEST = $(SRC_TEST:.c=.o)

all: gc test

gc: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c %.h
	$(CC) $(CFLAGS) $*.c $*.h -c

%.o: %.c
	$(CC) $(CFLAGS) $< -c

tests/%.o: %.c %.h
	@echo $< 
	$(CC) $(CFLAGS) $*.c $*.h -c

tests/%.o: %.c
	@echo $< 
	$(CC) $(CFLAGS) $< -c

run: gc
	./$(NAME)

run_test: test
	./test

test:	$(SRC_TEST)
	$(CC) $(CFLAGS) $(SRC_TEST) -lcunit -o test

valgrind: all
	valgrind --leak-check=yes ./$(NAME)

clean:
	rm -f *.o
	rm -f *~
	rm -f *#
	rm -f *.gch
	rm -f test
	rm -f gc

docs:
	doxygen Doxyfile

.PHONY = valgrind clean run
