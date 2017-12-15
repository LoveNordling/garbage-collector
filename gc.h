#ifndef GC_H
#define GC_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct heap heap_t;

heap_t* h_init(size_t bytes, bool unsafe_stack, float gc_threshold);
void h_delete(heap_t* h);
void h_delete_dbg(heap_t* h, void* dbg_value);

void* h_alloc_struct(heap_t* h, char* layout);
void* h_alloc_data(heap_t* h, size_t bytes);

size_t h_gc(heap_t* h);
size_t h_gc_dbg(heap_t* h, bool unsafe_stack);
size_t h_avail(heap_t* h);
size_t h_used(heap_t* h);

#endif /* GC_H */