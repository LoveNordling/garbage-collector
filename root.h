#ifndef ROOT_H
#define ROOT_H
#include <stdbool.h>

#include "gc.h"
#include "stdio.h"
/// Scan the roots of the program and perform a garbage collection
///
/// This function will scan the register, stack and static memory 
/// of the program and will perform a compaction of alive objects
/// on the fly.
///
/// \param h the heap
/// \param alloc_map the allocation alloc_map
/// \return the number of bytes collected
size_t scan_roots(void* h, bool* alloc_map);

/// Determines if a pointer is within the address range of a heap
///
/// \param h the heap
/// \param p the pointer
/// \return whether it points to the heap
bool is_pointer_to_heap(void* h, int* p);

size_t stack_size();

#endif /* ROOT_H */
