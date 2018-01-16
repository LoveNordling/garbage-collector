#include <stdlib.h>
#include <math.h>
#include "test_bits.h"

/**
*********************************************************************************
************************ TEST BIT-VECTOR FUNCTIONS ******************************
*********************************************************************************
*/

void test_set_bit()
{
    uintptr_t bit = 0;
    uintptr_t cmp = 1;

    bit = set_bit(bit, 0, 1);

    //IF BOTH ARE 1
    CU_ASSERT_EQUAL(bit, cmp);

    bit = set_bit(bit, 8, 1);
    cmp = 257;

    //IF BOTH ARE 257
    CU_ASSERT_EQUAL(bit, cmp);


    bit = set_bit(0, 63, 1);
    cmp = 0 | 1UL << 63;

    //IF MSB IS 1
    CU_ASSERT_EQUAL(bit, cmp);
}

void test_get_lsbs()
{
    uintptr_t zero = 0;
    uintptr_t three = 3;

    CU_ASSERT_EQUAL(get_lsbs(zero), 0);

    CU_ASSERT_NOT_EQUAL(get_lsbs(three), 2);
    
}

void test_set_lsbs()
{
    uintptr_t bit = 0;
    uintptr_t cmp = 1;

    bit = set_lsbs(bit, 1);

    CU_ASSERT_EQUAL(get_lsbs(bit),get_lsbs(cmp));

    cmp = 131;
    bit = set_lsbs(bit, 2);
    CU_ASSERT_NOT_EQUAL(get_lsbs(bit),get_lsbs(cmp));

    bit = set_lsbs(bit, 3);

    CU_ASSERT_EQUAL(get_lsbs(bit),get_lsbs(cmp));
}

void test_lsbs_are_zero()
{
    uintptr_t test = 0;

    CU_ASSERT_TRUE(lsbs_are_zero(test));
}

void test_lsbs_to_zero()
{
    uintptr_t test = 7;

    test = lsbs_to_zero(test);
    CU_ASSERT_TRUE(lsbs_are_zero(test));

    test = 3;
    test = lsbs_to_zero(test);

    CU_ASSERT_EQUAL(test, 0);
}


void test_set_msb()
{
    uintptr_t test = 0;

    test = set_msb(test, 1);

    CU_ASSERT_NOT_EQUAL(test,0);

    test <<= 1;
    
    CU_ASSERT_EQUAL(test, 0);
    
}

void test_get_msb()
{
    uintptr_t test = 0;

    CU_ASSERT_EQUAL(get_msb(test), 0);
     
    test = set_msb(test, 1);

    CU_ASSERT_EQUAL(get_msb(test), 1);
}

void test_new_bv_layout()
{
    
    uintptr_t layout = new_bv_layout("**iif", 40);
    uintptr_t layout_3_star = new_bv_layout("***", 24);
    uintptr_t layout_3_r = new_bv_layout("fil", 24);
    uintptr_t layout_empty = new_bv_layout("\0", 0);
    //bv_to_str = **rrr
    //char* temp;
    
    char* temp = bv_to_str(layout_3_star);
    CU_ASSERT_STRING_EQUAL("***", temp );
    free(temp);
    
    temp = bv_to_str(layout_3_r);
    CU_ASSERT_STRING_EQUAL("rrr", temp);
    free(temp);
    
    temp = bv_to_str(layout_empty);
    CU_ASSERT_STRING_EQUAL("\0", temp);
    free(temp);
    
    temp = bv_to_str(layout);
    CU_ASSERT_STRING_EQUAL("**rrr", temp);
    free(temp);
    
}

void test_new_bv_size()
{
    uintptr_t bv = new_bv_size(1000);

    uintptr_t bv_raw = 4003;

    CU_ASSERT_EQUAL(bv, bv_raw);
    // bv = new bv size 1000
    // raw = 4003
    // 

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
