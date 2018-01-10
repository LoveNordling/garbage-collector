#include <stdbool.h>
#include <stdlib.h>
#include "memorymap.h"
#include <stdio.h>
#include <math.h>

struct memorymap {
    void* start_of_heap;
    int memoryslots;
    bool* mem_array;
};

memorymap_t* memorymap_new(void* start_of_heap, int memoryslots, void* address)
{

    memorymap_t* mem = address;//(memorymap_t*) malloc(sizeof(memorymap_t));
    mem -> start_of_heap = start_of_heap;
    mem -> memoryslots = memoryslots;
    mem -> mem_array = address + sizeof(memorymap_t);//malloc(sizeof(bool)* (heap_size/min_allocsize));
    //address = address + memoryslots;
    bool * bool_array;
 
    for(int i = 0; i != memoryslots; i++)
    {
        bool_array = (mem -> mem_array) + i;
        *bool_array = false;
    }
    return mem;
  
}

bool memorymap_address_is_taken(memorymap_t* mem, void* address)
{
    int offset = address - mem -> start_of_heap;
    return mem-> mem_array[offset];
}

void memorymap_address_change(memorymap_t * mem, void * address)

{//sizeof(uintptr_t)
    int offset = address - mem->start_of_heap;
    if(mem-> mem_array[offset])
    {
      
        mem-> mem_array[offset] = false;
    }
    else{
    
        mem-> mem_array[offset] = true;
    }
  
    return;
}

void memorymap_delete(memorymap_t *mem)
{
    free(mem -> mem_array);
    free(mem); 
}

memorymap_t* memorymap_set_startofheap(memorymap_t* mem, void* address)
{
    mem -> start_of_heap = address;
    return mem;
}
    
void memorymap_print(memorymap_t *mem)
{

    bool* bool_array;
    for(int i = 0; i != (mem -> memoryslots); i++){
        bool_array = (mem -> mem_array) + i;
    
        if((*bool_array) ==true){
            puts("ALLOCATED");
        }
        else{
            puts("_______");
        }
    }
}

size_t memorymap_size()
{
    return sizeof(memorymap_t);
}

/*
  int main(){
  void * p;
  int b = 2000;
  void* memory;
    
  posix_memalign(&p, pow(2, 16), b);

  posix_memalign(&memory, pow(2, 16), b);
  char * hej = "hej";
  memorymap_t *mem = memorymap_new(p, 3, memory);

  memorymap_adress_change(mem, p+2);//Forgetting that I put this line here ruined 2h of my day.
  memorymap_print(mem);
  bool * pointi = calloc(1,sizeof(bool));
  printf("%d\n", *pointi);
  *(pointi+53465) = true;
  printf("%d\n", *(pointi+53465))
  }*/

