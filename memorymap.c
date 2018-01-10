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


memorymap_t* memorymap_new(void* start_of_heap, int memoryslots, void* adress)
{

  memorymap_t* mem = adress;//(memorymap_t*) malloc(sizeof(memorymap_t));
  mem -> start_of_heap = start_of_heap;
  mem -> memoryslots = memoryslots;
  mem -> mem_array = adress + sizeof(memorymap_t);//malloc(sizeof(bool)* (heap_size/min_allocsize));
  //adress = adress + memoryslots;
  bool * bool_array = mem->mem_array;
 
  for(int i = 0; i != memoryslots; i++)
    {
      bool_array[i] = false;
      /*
        bool_array = (mem -> mem_array) + i;
        *bool_array = false;
        */
    }
  return mem;
}

bool memorymap_adress_is_taken(memorymap_t* mem, void* adress)
{
  int offset = (adress - mem -> start_of_heap)/8;
    if(offset >=0 && offset <= mem->memoryslots)
      {
        return mem-> mem_array[offset];
      }
    return false;
}

void memorymap_adress_change(memorymap_t * mem, void * adress)
{//sizeof(uintptr_t)
    int offset = adress - mem->start_of_heap;
    if(mem-> mem_array[offset/8])
    {
      
        mem-> mem_array[offset/8] = false;
    }
    else{
    
        mem-> mem_array[offset/8] = true;
    }
  
    return;
}

void memorymap_delete(memorymap_t *mem)
{
    free(mem -> mem_array);
    free(mem); 
}

memorymap_t* memorymap_set_startofheap(memorymap_t* mem, void* adress)
{
    mem -> start_of_heap = adress;
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


void memorymap_update(memorymap_t* memmap, cell_t* cell_array, int cell_count)
{
  for (int i = 0; i < cell_count; i++) {
    if(!cell_is_active(&cell_array[i]))
      {
        int cell_size = CELL_SIZE/8;
        for (int j = i*cell_size; j < (i + 1)*cell_size; j++)
          {
            memmap->mem_array[j] = false;
          }
      }
  }
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
    printf("%d\n", *(pointi+53465));
}*/

