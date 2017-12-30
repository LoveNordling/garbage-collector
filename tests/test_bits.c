//#include "CUnit/CUnit.h"
#include "CUnit/Basic.h"
#include <stdlib.h>
#include <math.h>
#include "bits.h"



void test_layout_sizenumber(void)
{
  uintptr_t size_vector = new_bv_size(365);
  uintptr_t comp_vector = 365;

  CU_ASSERT_EQUALS(comp_vector, bv_size(size_vector));

}
