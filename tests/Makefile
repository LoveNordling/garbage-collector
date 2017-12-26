CC = gcc
CFLAGS = -std=c99 -ggdb -Wall
LDFLAGS = -lcunit
TEST = test

SRC_TEST := $(wildcard *.c)
HDR_TEST := $(wildcard *.h);
OBJ_TEST = $(SRC_TEST:.c=.o)

test:	$(OBJ_TEST)
	$(CC) $(CFLAGS) -o $(TEST) $(OBJ_TEST) $(LDFLAGS)

run_test: test
	./$(TEST)

%.o: %.c %.h
	$(CC) $(CFLAGS) $*.c $*.h -c

%.o: %.c
	$(CC) $(CFLAGS) $< -c

valgrind: test
	valgrind --leak-check=yes ./$(TEST)

clean:
	rm -f $(OBJ_TEST) $(TEST) *~
	rm -f *#
	rm -f *.gch

docs:
	doxygen Doxyfile

.PHONY = valgrind clean run
