#ifndef COMPACT_H
#define COMPACT_H

#include "gc.h"
#include "memorymap.h"

size_t traverse_root(heap_t* h, void* p, uintptr_t* rp, memorymap_t* alloc_map);


#endif /* COMPACT_H */
