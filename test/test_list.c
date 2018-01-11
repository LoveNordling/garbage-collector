#include "test_list.h"
#include "list.h"
#include <stdlib.h>

void print_elem(elem_t elem, void* p)
{
  printf("%i, ",elem.i);
}
void test_linked_list()
{
  heap_t* h = h_init(100000, true, 0.5f);
  list_t* list = list_new(NULL, NULL, NULL, h);
  size_t size = 400;
  size_t delete_every = 4;
  for(int i = 0; i < size/delete_every; i++)
    {
      for (int j = 0; j < delete_every; j++) {
         
        elem_t elem;
        elem.i = i*delete_every+j;
        list_prepend(list, elem);
        //list_apply(list, print_elem, NULL); 
      }
      list_remove(list, 0, false);
    }
  
  for(int i = 0; i < list_length(list); i++)
    {
      int x;
      list_get(list, i, &x);
      CU_ASSERT_EQUAL(x, size/delete_every+i);
    }
  
  //size_t freed = h_gc(h);
  //printf("Cleaned up %lu bytes\n", freed);
  list_apply(list, print_elem, NULL);
  h_delete(h);
}

