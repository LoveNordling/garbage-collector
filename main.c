#include <stdio.h>
#include "gc.h"
#include "gc_utils.h"
#include <math.h>

typedef struct test test_t;

struct test
{
  int* x;
  int* y;
  int z;
};



int main(int argc, char** argv)
{
	#ifdef _WIN32
	puts("windows");
	#endif
	
	#ifdef __linux__
	puts("linux");
	#endif
	
	#ifdef __unix__
	puts("unix");
	#endif
        heap_t* h = h_init(1000000, false, 0.5f);
        test_t* obj = (test_t*)h_alloc_struct(h, "**i");
        // h_print_cells(h);
        
        obj->x = (int*)h_alloc_struct(h, "i");
        obj->y = (int*)h_alloc_struct(h, "i");
        *(obj->x) = 1;
        *(obj->y) = 2;
        printf("x = %i, y = %i \n", *(obj->x), *(obj->y));
        int* z = (int*)h_alloc_struct(h, "i");
        *z = 9;
        printf("\nZ=%d\n", *z);
        z = obj->x;
        
        printf("\nZ=%d\n", *z);
        //obj = NULL;
        //z = NULL;
        size_t bytes = h_gc(h);
        printf("released %lu bytes \n", bytes);
        printf("x = %i, y = %i \n", *(obj->x), *(obj->y));
        h_delete(h);
        
	return 0;
        }
