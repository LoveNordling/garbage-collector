#include "test_list.h"
#include "list.h"
#include <stdlib.h>

void test_linked_list()
{
  heap_t* h = h_init(1000000, true, 0.5f);
  list_t* list = list_new(NULL, NULL, NULL, h);

  size_t size = 1000;
  /*
    for(int i = 0; i < size; i++)
      {
        int* j = h_alloc_struct(h, "i");
        *j = i;
        elem_t elem;
        elem.p = j;
        list_append(list, elem);
      }
  */
}
