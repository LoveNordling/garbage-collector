#include <stdlib.h>
#include <math.h>
#include "test_bits.h"


void test_print_bits()
{
    uintptr_t test = 1UL << 2;
    //print_bits(test);
}

/**
*********************************************************************************
************************ TEST BIT-VECTOR FUNCTIONS ******************************
*********************************************************************************
*/



void test_new_bv_layout()
{
  uintptr_t layout = new_bv_layout("**iif", 40);
  uintptr_t layout_3_star = new_bv_layout("***", 24);
  uintptr_t layout_3_r = new_bv_layout("fil", 24);
  //uintptr_t layout_empty = new_bv_layout(" ", 0);
  //bv_to_str = **rrr
 
  char *bv_from_layout = bv_to_str(layout);
  char *bv_from_layout1 = bv_to_str(layout_3_star);
  char *bv_from_layout2 = bv_to_str(layout_3_r);
  printf("This is the string:%s\n", bv_from_layout);


  CU_ASSERT_STRING_EQUAL("***", bv_from_layout1 );
  CU_ASSERT_STRING_EQUAL("rrr", bv_from_layout2 );
  //CU_ASSERT_STRING_EQUAL(" ", layout_empty );
  CU_ASSERT_STRING_EQUAL("**rrr", bv_from_layout);
}

void test_new_bv_size()
{
  uintptr_t bv = new_bv_size(1000);
  
  uintptr_t bv_raw = 4003;

  CU_ASSERT_EQUAL(bv, bv_raw);
  print_bits(bv);
  print_bits(bv_raw);

}

void test_bv_size()
{
    uintptr_t size_vector = new_bv_size(365);
    uintptr_t layout_vector = new_bv_layout("*i*", 24);
    //print_bits(size_vector);
    //print_bits(layout_vector);
    
    uintptr_t comp_size_vector = 365;
    uintptr_t comp_layout_vector = 24;
    //print_bits(comp_size_vector);
    //print_bits(comp_layout_vector);

    CU_ASSERT_EQUAL(comp_size_vector, bv_size(size_vector));
    CU_ASSERT_EQUAL(comp_layout_vector, bv_size(layout_vector));

    //print_bits(bv_size(size_vector));
}

void test_set_bit();
void test_set_lsbs();
void test_get_lsbs();
void test_lsbs_to_zero();
void test_lsbs_are_zero();
void test_set_msb();
void test_get_msb();
