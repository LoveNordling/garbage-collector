#include <stdlib.h>
#include <CUnit/CUnit.h>
#include <string.h>
#include "gc.h"
#include "test_gc.h"

void test_gc_init_delete(){

  
  heap_t * h= h_init(500, true, 20);
  CU_ASSERT_TRUE(h != NULL);
  h_delete(h);

  h= h_init(-33, true, 20);
  CU_ASSERT_TRUE(h != NULL);
  h_delete(h);


  h= h_init(99999999999999, true, 20);
  CU_ASSERT_TRUE(h != NULL);
  h_delete(h);
}
