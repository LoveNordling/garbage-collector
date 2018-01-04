#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <stdlib.h>
#include <math.h>
#include "../root.h"


void test_is_pointer_to_heap()
{
  if(false)
    {
      heap_t* h = h_init(1000, false, 0.5f);
      int* p = (int*)h + 200;
      CU_ASSERT_EQUAL(is_pointer_to_heap(h, p), true);
    }
}




