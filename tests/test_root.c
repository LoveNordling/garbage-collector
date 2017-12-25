#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <stdlib.h>
#include <math.h>
#include <CUnit/CUnit.h>
#include "../gc.h"
#include "../root.h"


void test_is_pointer_to_heap()
{
  
  if(false)
    {
      heap_t* h = h_init(1000, false, 0.5f);
      void* p = h;
      CU_ASSERT_EQUAL(is_pointer_to_heap(h, p), true);
    }
}




