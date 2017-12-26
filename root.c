#include <stdio.h>
#include <setjmp.h>
#include "root.h"

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

//these three functions should perhaps be moved to another source file
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
    printf("traversing stack of size %lu ...\n\n", stack_size());

    int** sp = stack_get_end();
    int** s_start = stack_get_start();

    for(int i = 0; sp < s_start; ++i)
    {
        ++sp;

        if(is_pointer_to_heap(h, (int*) *sp))
        {
            printf("found possible pointer at address: %p    value: %p\n", sp, (int*) *sp);

            //TODO: (sprint 3)
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
