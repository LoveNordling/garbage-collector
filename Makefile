CC = gcc
CFLAGS = -std=c99 -ggdb -Wall
NAME = gc

SRC := $(wildcard *.c)
HDR := $(wildcard *.h);
OBJ = $(SRC:.c=.o)

all: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c %.h
	$(CC) $(CFLAGS) $*.c $*.h -c

%.o: %.c
	$(CC) $(CFLAGS) $< -c

run: all
	./$(NAME)
	
test:
	$(CC) $(CFLAGS) $(SRC) "test/test.c" -lcunit

valgrind: all
	valgrind --leak-check=yes ./$(NAME)

clean:
	rm -f *.o
	rm -f *~
	rm -f *#

docs:
	doxygen Doxyfile

.PHONY = valgrind clean run
