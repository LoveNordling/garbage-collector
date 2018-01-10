
#include "test_integration.h"

#include "../gc.h"
#include <stdio.h>

void test_gc()
{
  heap_t* h = h_init(100000, false, 0.5f);
  int num_ints = 200;
  
  int** ints = h_alloc_struct(h, "200*");
  int save_every = 50;
  int* x;
  //void* data = h_alloc_data(h, 32);
  for(int i = 0; i < num_ints*save_every; i++)
    {
      //puts("allocing\n");
      int* j = h_alloc_struct(h, "i");
      *j = i;
      if(i % save_every == 0)
        {          
          ints[i/save_every] = j;
        }
    }
  puts("\n\n");
  /*
  for (int i = 0; i < 10; i++) {
    h_gc(h);
    }*/
  
  for(int i = 0; i < num_ints; i++)
    {
      printf("ints[%i] = %i, ", i, *(ints[i]));
      
    }

  h_delete(h);

}
