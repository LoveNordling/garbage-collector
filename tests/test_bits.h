#ifndef TEST_BITS_H
#define TEST_BITS_H

#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

#include "../bits.h"

void test_print_bits();
void test_new_bv_layout();
void test_new_bv_size();
void test_bv_size();

void test_set_bit();
void test_set_lsbs();
void test_get_lsbs();
void test_lsbs_to_zero();
void test_lsbs_are_zero();
void test_set_msb();
void test_get_msb();

#endif /* TEST_BITS_H */
