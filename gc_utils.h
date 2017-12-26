#ifndef GC_UTILS_H
#define GC_UTILS_H

#include "gc.h"

/// Returns the size of the heap
/// 
/// \param h the heap
/// \return the size in bytes
size_t h_size(heap_t* h);

/// Returns a pointer to the beginning of the heap's
/// allocated memory block
///
/// \param h the heap
/// \return the start of the heap's data segment
void* h_data(heap_t* h);

#endif /* GC_UTILS_H */