
#include "test_integration.h"

#include "../gc.h"
#include <stdio.h>

void test_gc()
{
  heap_t* h = h_init(1000000, false, 0.5f);
  int num_ints = 1000000;
  int** ints = calloc(num_ints, sizeof(int*));
  int save_every = 100;
  for(int i = 0; i < num_ints*save_every; i++)
    {
      int* j = h_alloc_struct(h, "i");
      *j = i;

      if(i % save_every == 0)
        {
          
          ints[i/save_every] = j;
        }
    }
  puts("\n\n");
  for(int i = 0; i < num_ints; i++)
    {
      printf("ints[%i] = %i, ", i, *(ints[i]));
      
    }

  h_delete(h);

}
