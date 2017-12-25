#include <stdbool.h>
#include <stdlib.h>
#include "memorymap.h"
#include <stdio.h>

struct memorymap {
  void * start_of_heap;
  int heap_size;
  int min_allocsize;
  bool *mem_array;
};


memorymap_t* memorymap_new(void * start_of_heap, int heap_size, int min_allocsize){

  memorymap_t * mem = (memorymap_t*) malloc(sizeof(memorymap_t));
  mem -> start_of_heap = start_of_heap;
  mem -> heap_size = heap_size;
  mem -> min_allocsize = min_allocsize;
  mem -> mem_array = malloc(sizeof(bool)* (heap_size/min_allocsize));//arrays are weird please fix if you know how they work ^_^

  return mem;
  
}

bool memorymap_adress_is_taken(memorymap_t* mem, void * adress){
  int offset = adress - mem->start_of_heap;
  return mem-> mem_array[offset];
}

void memorymap_adress_change(memorymap_t * mem, void * adress, int size){
  int offset = adress - mem->start_of_heap;
  if(mem-> mem_array[offset])
    {
      mem-> mem_array[offset] = false;
    }
  else{
    mem-> mem_array[offset] = true;
  }
  return;
}

void memorymap_print(memorymap_t *mem){
  for(int i = 0; i<=(mem->heap_size/mem->min_allocsize);i++){
    bool * mem_a = mem -> mem_array;
    if(*mem_a){
      puts("ALLOCATED/n");
    }
    else{
      puts("_______");
    }
  }
}
/*bool memorymap_adress_is_taken(memorymap_t* mem, void * adress){

  }*/

int main(){
  char * hej = "hej";
  memorymap_t *mem = memorymap_new(hej, 10, 2);
  memorymap_print(mem);
}
