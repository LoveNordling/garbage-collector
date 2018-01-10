CC = gcc
CFLAGS = -I ../ -std=c99 -ggdb -Wall  -fprofile-arcs -ftest-coverage -pg -no-pie
LDFLAGS = -lcunit  -fprofile-arcs -ftest-coverage -pg -no-pie
TEST = test

SRC_TEST := $(wildcard *.c)
HDR_TEST := $(wildcard *.h);
OBJ_TEST = $(SRC_TEST:.c=.o)

ALL_SRCS := $(wildcard ../*.c)
SRC := $(filter-out ../main%.c, $(ALL_SRCS))
OBJ_SRC = $(SRC:.c=.o)

test:	$(OBJ_TEST) objsrc
	$(CC) $(CFLAGS) -o $(TEST) $(OBJ_TEST) $(OBJ_SRC) $(LDFLAGS)

objsrc:	
	$(MAKE) -C ../ gc

run_test: test
	./$(TEST)

debug: test
	gdb ./$(TEST)

gcov: $(SRC) $(SRC_TEST)
	$(CC) $(CFLAGS)  $(SRC) $(SRC_TEST) -o gcov_test $(LDFLAGS)


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
	rm -f *.gcno
	rm -f *.gcda
docs:
	doxygen Doxyfile

.PHONY = valgrind clean run
