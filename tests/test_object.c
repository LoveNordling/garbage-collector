#include "test_object.h"
#include <stdlib.h>



void test_new_object()
{
  int x = 15;
  int *xp = &x;
  
  void *memory_start = calloc(10, sizeof(void *));
  memory_start = new_object(memory_start+sizeof(void*), "**", 24);

  memory_start = &x;
  int *new_ptr = memory_start;
  //new_ptr = new_ob;
  //new_ptr = xp;

  printf("memory_start address: %p memory_start value: %p\n", &memory_start, memory_start);
  CU_ASSERT_EQUAL(x, *new_ptr);
  printf("X is %d, *new_ptr %d", x, *new_ptr);
    
}


void test_object_copy()
{

  int x = 15;
  
  int *xp = &x;
  
  void *memory_start = calloc(10, sizeof(void*));
  void *new_ob = new_object(memory_start+sizeof(void*), "**", 24);

  int *new_ptr;
  new_ptr= &new_ob;
  new_ptr = xp;

  void *cpy_memory_start = calloc(10, sizeof(void *));
  cpy_memory_start = cpy_memory_start + sizeof(void*);
  object_copy(new_ob, cpy_memory_start);
  int *int_copied = cpy_memory_start+sizeof(void*);
   
  
  CU_ASSERT_EQUAL(*new_ptr, *int_copied );
  printf("original object is %p, int_copied is %p\n", &(*new_ptr), int_copied);
  printf("Address where the copy lies: %p", cpy_memory_start);
}


void test_object_is_copied()
{

}


void test_set_forwarding_address()
{

}


void test_get_forwarding_address()
{

}


void test_get_object_size()
{

}


void test_format_string_parser()
{

}


