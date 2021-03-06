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

//dump values stored in the registers onto the stack
#define dump_registers()                        \
    jmp_buf env;                                \
    if(setjmp(env)) abort();                    \

//returns end/top of stack  (this is the address of the latest entry to the stack)
void* stack_get_end()
{
    return __builtin_frame_address(0);
}

//returns start/bottom of stack (this is the address of the first entry to the stack)
void* stack_get_start()
{
	#ifdef _WIN32
	return STACK_START_P;
	#else
	return environ;
	#endif
}

//returns the size of the stack in bytes
size_t stack_size()
{
	return (size_t) (((char*) stack_get_start()) - ((char*) stack_get_end()));
}

//determines if p is pointing anywhere within the heap's data region
bool is_pointer_to_heap(heap_t* h, void* p)
{
	//get the bounds of the heap's allocation region
	void* data_start = (void*) h_data(h);
	void* data_end = (void*) ((char*) h_data(h)) + h_size(h);

	//do a range check
	return p >= data_start && p <= data_end;
}


//these three functions should perhaps be moved to another source file
//TODO: (sprint 3)   
bool is_secure_pointer(void* p, memorymap_t* alloc_map)
{
    return memorymap_adress_is_taken(alloc_map, p);
}

//TODO: (sprint 3)
void activate_cell(heap_t* h, void* p)

{
  cell_t* cell = h_get_cell(h, p);
  cell_activate(cell);
}


//scan the stack for roots and traverse them if found
size_t scan_stack(heap_t* h, memorymap_t* alloc_map)
{
	printf("traversing stack of size %lu...\n\n", stack_size());
        
    size_t freed_memory = 0;

    //get boundary addresses of the stack (sp = stack pointer)
	char* sp = (char*) stack_get_end();
	char* stack_start = (char*) stack_get_start();
        int numroots = 0;
	//loop through the stack (the stack is like a consecutive array of data)
	for(int i = 0; sp < stack_start; ++i)
	{
            //interpet the data at sp as a 4/8 byte pointer root
          //sp += sizeof(uintptr_t);
		void* p = (void *)*(uintptr_t*) sp;
		
		void* root = (void*) *(uintptr_t*) sp;

		//determine if the root is pointing inside the heap (most values will get filtered away here)
		if(is_pointer_to_heap(h, root))
		{
                  //printf("found pointer\n");
			//copy and traverse secure roots
			if (is_secure_pointer(root, alloc_map))
			{
                          numroots++;
                            freed_memory += traverse_root(h, p, (uintptr_t*) sp, alloc_map);
			}
			//otherwise deactivate their targeted cells
			else
			{
                          //activate_cell(h, p);
			}
		}

		//increment the stack pointer by 4/8 bytes
		sp += sizeof(uintptr_t);
	}
        printf("\n\n Number of roots: %i\n\n", numroots);

	return freed_memory;
}


//scan the register, stack and static/global memory region for pointers to the heap
size_t scan_roots(heap_t* h, memorymap_t* alloc_map)
{
    size_t freed_memory = 0;

    dump_registers();
    freed_memory += scan_stack(h, alloc_map);

    return freed_memory;
}
