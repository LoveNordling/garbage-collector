#include <stdio.h>
#include <setjmp.h>
#include "root.h"
#include "gc_utils.h"

#ifdef _WIN32
extern void* STACK_START_P;
#else
extern char** environ;
#endif

#define dump_registers()      \
	jmp_buf env;              \
	if(setjmp(env)) abort();  \

char* stack_get_end()
{
	return __builtin_frame_address(0);
}

char* stack_get_start()
{
	#ifdef _WIN32
	return STACK_START_P;
	#else
	return (char*)&environ;
	#endif
}

size_t stack_size()
{
	return stack_get_start() - stack_get_end();
}

bool is_pointer_to_heap(heap_t* h, void* p)
{
	return p >= (void*)h_data(h) && (char*)p <= ((char*)h_data(h)) + h_size(h);
}


//these three functions should perhaps be moved to another source file
//TODO: (sprint 3)   
bool is_secure_pointer(heap_t* h, void* p, bool* alloc_map)
{
	return false;
}

//TODO: (sprint 3)
void deactivate_cell(heap_t* h, void* p)
{

}

//TODO: traverse the heap starting from a root (sprint 3)
void traverse_root(heap_t* h, void* p, uintptr_t* rp)
{
  
  /*
  if(object_is_copied(p))
    {
    }
  else
    {
      char* op = p;
      char* s = object_get_format_string(p);
      while(*s)
        {
          if(*s == '*')
            {
              traverse_root(h, (void*)*(void**)op, (uintptr_t*)op);
            }
          s++;
        }
      void* new_object = h_alloc_struct(h, s);
      object_copy(p, new_object);
      object_set_forwarding_address(p, new_object);
    }
  
  *rp = object_get_forwarding_address(p);
  */
}


size_t scan_stack(heap_t* h, bool* alloc_map)
{
	printf("traversing stack of size %lu...\n\n", stack_size());

	char* sp = stack_get_end();
	char* s_start = stack_get_start();

	for(int i = 0; sp < s_start; ++i)
	{
		sp += sizeof(uintptr_t);
		void* p = (void*) *(uintptr_t*) sp;

		if(is_pointer_to_heap(h, p))
		{
			printf("found possible pointer at address: %lu\tvalue: %lu\n", (uintptr_t) sp, (uintptr_t) p);

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
