#ifndef ROOT_H
#define ROOT_H

#include "gc.h"

/// Scan the roots of the program and perform a garbage collection
///
/// This function will scan the register, stack and static memory 
/// of the program and will perform a compaction of alive objects
/// on the fly.
///
/// \param h the heap
/// \param alloc_map the allocation alloc_map
/// \return the number of bytes collected
size_t scan_roots(heap_t* h, bool* alloc_map);

#endif /* ROOT_H */