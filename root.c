#include <stdio.h>
#include <setjmp.h>
#include "root.h"

#ifdef _WIN32
#define STACK_GROWTH_DIRECTION 1
extern void* STACK_START_P;
#else
#define STACK_GROWTH_DIRECTION 1
extern char** environ;
#endif

#define dump_registers()   \
	jmp_buf env;             \
	if(setjmp(env)) abort(); \

void* stack_get_end()
{
	return __builtin_frame_address(0);
}

void* stack_get_start()
{
	#ifdef _WIN32
	return STACK_START_P;
	#else
	return &environ;
	#endif
}

size_t stack_size()
{
	return stack_get_start() - stack_get_end();
}

bool is_pointer_to_heap(heap_t* h, int* p)
{
	return (void*)p >= (void*)h && (char*)p <= ((char*)h) + h_size(h);
}

//TODO: (sprint 3)
bool is_secure_pointer(heap_t* h, int* p, bool* alloc_map)
{
    return false;
}

//TODO: (sprint 3)
void deactivate_cell(heap_t* h, int* p)
{

}

//TODO: traverse the heap starting from a root (sprint 3)
void traverse_root(heap_t* h, int** p)
{
	
}

size_t scan_stack(heap_t* h, bool* alloc_map)
{
	printf("traversing stack of size %d...\n\n", stack_size());

	int* sp = stack_get_end();

	for(int i = 0; sp < (int*) stack_get_start(); ++i)
	{
		sp += STACK_GROWTH_DIRECTION;

		if(is_pointer_to_heap(h, (int*) *sp))
		{
			if (is_secure_pointer(h, (int*) *sp, alloc_map))
			{
				traverse_root(h, (int**) sp);
			}
			else
			{
				deactivate_cell(h, (int*) *sp);
			}
		}
	}

	return 0;
}

size_t scan_roots(heap_t* h, bool* alloc_map)
{
	size_t freed_memory = 0;

	dump_registers();
	freed_memory += scan_stack(h, alloc_map);

	return freed_memory;
}
