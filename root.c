#include <stdio.h>
#include <setjmp.h>
#include "root.h"
#include "compact.h"
#include "gc_utils.h"


#ifdef _WIN32
extern void* STACK_START_P;
#else
extern char** environ;
#endif

#define dump_registers()                        \
    jmp_buf env;                                \
    if(setjmp(env)) abort();                    \

void* stack_get_end()
{
    return __builtin_frame_address(0);
}


void* stack_get_start()
{
	#ifdef _WIN32
	return STACK_START_P;
	#else
	return environ;
	#endif
}

size_t stack_size()
{
  return (uintptr_t)stack_get_start() - (uintptr_t)stack_get_end();
}


bool is_pointer_to_heap(heap_t* h, void* p)
{
	return p >= (void*)h_data(h) && (char*)p <= ((char*)h_data(h)) + h_size(h);
}


//these three functions should perhaps be moved to another source file
//TODO: (sprint 3)   
bool is_secure_pointer(heap_t* h, void* p, bool* alloc_map)
{
	return true;
}

//TODO: (sprint 3)
void deactivate_cell(heap_t* h, void* p)
{
  
}



size_t scan_stack(heap_t* h, bool* alloc_map)
{
	printf("traversing stack of size %lu...\n\n", stack_size());

	void* sp = stack_get_end();
	void* s_start = stack_get_start();

	for(int i = 0; sp < s_start; ++i)
	{
		sp += sizeof(uintptr_t);
		void* p = (void*) *(uintptr_t*) sp;

		if(is_pointer_to_heap(h, p))
		{
			printf("found possible pointer at address: %lu\tvalue: %lu\n", (uintptr_t) sp, *(uintptr_t*) p);

			//TODO: (sprint 3)
			if (is_secure_pointer(h, p, alloc_map))
			{
				traverse_root(h, p, (uintptr_t*) sp);
			}
			else
			{
				deactivate_cell(h, p);
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
