
#include "test_integration.h"

#include "../gc.h"
#include <stdio.h>

void test_gc()
{
  heap_t* h = h_init(1000000, false, 0.5f);
    
  int** ints = calloc(1000, sizeof(int));
  for(int i = 0; i < 1000000; i++)
    {
      int* j = h_alloc_struct(h, "i");
      *j = i;
      if(i % 1000 == 0)
        {
          ints[i/1000] = j;
        }
    }
  for(int i = 0; i < 1000; i++)
    {
      printf("%i, ", *ints[i]);
    }
  h_delete(h);
  
}
