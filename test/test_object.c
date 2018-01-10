#include "test_object.h"
#include <stdlib.h>
#include <stdint.h>

typedef struct test {
    int* first;
    int* second;
}test_t;



void test_new_object()
{
    int x = 15;
  
  
    void *memory_start = calloc(10, sizeof(void *));
    test_t *test = new_object(memory_start+sizeof(void*), "**", 24);

    test->first = &x;
    int *new_ptr = memory_start;

    CU_ASSERT_EQUAL(x, *(test->first));
    printf("X is %d, *(test->first) %d\n", x, *(test->first));
    
}


void test_object_copy()
{

    int x = 15;
  
  
    void *memory_start = calloc(10, sizeof(void*));
    test_t* test = new_object(memory_start+sizeof(void*), "**", 24);

    test->first = &x;
  
    void* cpy_memory_start = calloc(10, sizeof(void *));
    test_t *test2 = cpy_memory_start + sizeof(void*);

    object_copy((void*)test, (void*)test2);

   
  
    CU_ASSERT_EQUAL(*(test->first), *(test2->first));
    CU_ASSERT_NOT_EQUAL(&(test->first), &(test2->first));

}


void test_object_is_copied()
{
    int x = 15;
  
  
    void *memory_start = calloc(10, sizeof(void*));
    test_t* test = new_object(memory_start+sizeof(void*), "**", 24);

    test->first = &x;
  
    void* cpy_memory_start = calloc(10, sizeof(void *));
    test_t *test2 = cpy_memory_start + sizeof(void*);

    object_copy((void*)test, (void*)test2);

    CU_ASSERT_TRUE(object_is_copied(test));
    //klolla fv på första struktens pekares bvs layout
}


void test_set_forwarding_address()
{

    int x = 15;
  
  
    void *memory_start = calloc(10, sizeof(void*));
    test_t* test = new_object(memory_start+sizeof(void*), "**", 24);

    test->first = &x;
  
    void* cpy_memory_start = calloc(10, sizeof(void *));
    test_t *test2 = cpy_memory_start + sizeof(void*);

    object_copy((void*)test, (void*)test2);

    uintptr_t address = test2;
    uintptr_t address_in_bv = (uintptr_t)get_forward_address(test);
    //*((test->first)-sizeof(void*));
  
    CU_ASSERT_EQUAL(address_in_bv, address);
  
    //compare the address contained in the bv and the actual one


  
}


void test_get_forwarding_address()
{

    int x = 15;
  
  
    void *memory_start = calloc(10, sizeof(void*));
    test_t* test = new_object(memory_start+sizeof(void*), "**", 24);

    test->first = &x;
  
    void* cpy_memory_start = calloc(10, sizeof(void *));
    test_t *test2 = cpy_memory_start + sizeof(void*);

    object_copy((void*)test, (void*)test2);

    uintptr_t fw_address = (uintptr_t)get_forward_address(test);
  
    CU_ASSERT_EQUAL(fw_address, test2); 
  
}


void test_get_object_size()
{
    int x = 15;
    
    void *memory_start = calloc(10, sizeof(void*));
    test_t* test = new_object(memory_start+sizeof(void*), NULL , 24);

    test->first = &x;
  
    size_t test_size = get_object_size(test);

    CU_ASSERT_EQUAL(test_size, 24);
  
}



void test_get_object_size_layout()
{
    int x = 15;
    
    void *memory_start = calloc(10, sizeof(void*));
    test_t* test = new_object(memory_start+sizeof(void*), "**" , 24);

    test->first = &x;
  
    size_t test_size = get_object_size(test);

    CU_ASSERT_EQUAL(test_size, 24);
  
}

void test_format_string_parser()
{

    int x = 15;
  
    void *memory_start = calloc(10, sizeof(void *));
    test_t *test = new_object(memory_start+sizeof(void*), "**", 24);

    uintptr_t layout_bv = new_bv_layout("**", 16);
    uintptr_t translated_format_string = format_string_parser("**");
  
    test->first = &x;
  

    CU_ASSERT_EQUAL(16 ,translated_format_string);

  
}


