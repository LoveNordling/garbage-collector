#ifndef COMPACT_H
#define COMPACT_H

#include "gc.h"


size_t traverse_root(heap_t* h, void* p, uintptr_t* rp);


#endif /* COMPACT_H */
