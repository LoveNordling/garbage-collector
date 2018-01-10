CC = gcc                                                                        
CFLAGS = -std=c99 -ggdb -Wall                                                   
LDFLAGS =                                                                       
NAME = demo                                                              
SRC := $(wildcard *.c)                                                          
HDR := $(wildcard *.h);                                                         
OBJ = $(SRC:.c=.o)     

GC_SRCS := $(wildcard ../src/*.c)     
GC_SRC := $(filter-out ../src/main%.c, $(GC_SRCS))            
GC_HDR := $(wildcard ../src/*.h);                                              
GC_OBJ = $(GC_SRC:.c=.o)

all: demo

demo: $(OBJ) objsrc
	$(CC) $(CFLAGS) $(OBJ) $(GC_OBJ) -o $(NAME) $(LDFLAGS)                            
run: demo                                                                       
	./$(NAME)    

debug: demo                                                                     
	gdb ./gc

objsrc: 
	$(MAKE) -C ../src gc

%.o: %.c %.h                                                                  		$(CC) $(CFLAGS) $*.c $*.h -c         
%.o: %.c                                                                        
	$(CC) $(CFLAGS) $< -c                                                   
valgrind: all                                                                   
	valgrind --leak-check=yes ./$(NAME)                                     

clean:                                                                          
	$(MAKE) -C ../ clean
	rm -f $(OBJ) $(NAME)
	rm -f *#*                                                               
	rm -f *.gch                                                             

docs:                                                                           
	doxygen Doxyfile                                                        

.PHONY = valgrind clean run run_test                                          

