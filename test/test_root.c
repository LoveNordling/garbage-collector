#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <stdlib.h>
#include <math.h>
#include <CUnit/CUnit.h>
#include "root.h"


void test_is_pointer_to_heap(heap_t* h, bool* alloc_map)
{
  CU_ASSERT_EQUAL(is_pointer_to_heap(h, alloc_map), true);
}
