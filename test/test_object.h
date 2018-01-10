#ifndef TEST_OBJECT_H
#define TEST_OBJECT_H

#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "../src/object.h"

void test_new_object();
void test_object_copy();
void test_object_is_copied();
void test_set_forwarding_address();
void test_get_forwarding_address();
void test_get_object_size();
void test_get_object_size_layout();
void test_format_string_parser();

#endif /* TEST_OBJECT_H */
