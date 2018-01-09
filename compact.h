#ifndef COMPACT_H
#define COMPACT_H

#include "gc.h"
#include "memorymap.h"

size_t (heap_t* h, void* object_pointer, uintptr_t* heap_pointer, memorymap_t* alloc_map);


#endif /* COMPACT_H */
