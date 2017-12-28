#include <stdbool.h>
#include <stdlib.h>
#include "memorymap.h"
#include <stdio.h>
#include <math.h>

struct memorymap {
  void * start_of_heap;
  int heap_size;
  int min_allocsize;
  bool *mem_array;
};


memorymap_t* memorymap_new(void * start_of_heap, int heap_size, int min_allocsize)
{

  memorymap_t * mem = (memorymap_t*) malloc(sizeof(memorymap_t));
  mem -> start_of_heap = start_of_heap;
  mem -> heap_size = heap_size;
  mem -> min_allocsize = min_allocsize;
  mem -> mem_array = malloc(sizeof(bool)* (heap_size/min_allocsize));//arrays are weird please fix if you know how they work ^_^

  bool * bool_array;
 
  for(int i = 0; i != (heap_size/min_allocsize); i++)
    {
      bool_array = (mem -> mem_array) + i;
      *bool_array = false;
    }
  return mem;
  
}

bool memorymap_adress_is_taken(memorymap_t* mem, void * adress)
{
  int offset = adress - mem -> start_of_heap;
  return mem-> mem_array[offset];
}

void memorymap_adress_change(memorymap_t * mem, void * adress)
{
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

void memorymap_delete(memorymap_t *mem)
{
  free(mem -> mem_array);
  free(mem); 
}

void memorymap_print(memorymap_t *mem){
  int min_allocsize = mem -> min_allocsize;
  int heap_size = mem->heap_size;

  bool * bool_array;
  for(int i = 0; i != (heap_size/min_allocsize); i++){
    bool_array = (mem -> mem_array) + i;
    
    if((*bool_array) ==true){
      puts("ALLOCATED");
    }
    else{
      puts("_______");
      }
  }
}
/*
int main(){
  void * p;
  int b = 2000;
  posix_memalign(&p, pow(2, 16), b);
  
  char * hej = "hej";
  memorymap_t *mem = memorymap_new(p, 10, 2);

  memorymap_adress_change(mem, p+321);//Forgetting that I put this line here ruined 2h of my day.
  memorymap_print(mem);
  bool * pointi = calloc(1,sizeof(bool));
  printf("%d\n", *pointi);
  *(pointi+53465) = true;
  printf("%d\n", *(pointi+53465));
}

*/
