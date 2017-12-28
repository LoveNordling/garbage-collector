#include "test_memorymap.h"
#include "memorymap.h"
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <stdlib.h>
#include <math.h>
#include <CUnit/CUnit.h>

void test_memorymap()
{
    void* start_of_heap;
    posix_memalign(&start_of_heap, pow(2, 16), 2000);

    int heap_size = 20;
    int min_allocsize = 5;

  
    memorymap_t * mem = memorymap_new(start_of_heap, heap_size, min_allocsize);
    puts("2");
    memorymap_adress_change(mem, start_of_heap);

    CU_ASSERT_TRUE(memorymap_adress_is_taken(mem, start_of_heap));

    memorymap_delete(mem);
    free(start_of_heap);
    return;
}
