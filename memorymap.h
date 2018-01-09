#ifndef MEMORYMAP_H
#define MEMORYMAP_H
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
typedef struct memorymap memorymap_t;

/// Creates a new memorymap
///
/// \param start_of_heap used to to calculate what address everybool reperesnts.
/// \param heap_size used to determine how big of a stack we are representing.
/// \param min_alloc_size the lowest amount of memory a user is allowed to allocate. heap_size/min_allocsize = number of bools needed to represent the memory
/// \returns: a memorymap containing a bool for each possible allocation in the heap.
memorymap_t* memorymap_new(void* start_of_heap, int memoryslots, void* address);

/// Used to check if space is empty on stack
///
/// \param mem the memorymap to be checked
/// \param address the address to be checked

/// \returns: True if address is taken
bool memorymap_address_is_taken(memorymap_t* mem, void* address);


/// Flips the value of the address in the memorymap
///
/// \param mem the memorymap to be changed
/// \param address the address that we are changing
/// \param size the size of the object to be flipped.
/// \returns: True if address is taken
void memorymap_address_change(memorymap_t* mem, void* address);

/// Sets the start of heap to address
///
/// \param mem the memorymap to be changed
/// \param address the address that we are changing to
memorymap_t* memorymap_set_startofheap(memorymap_t* mem, void* address);

/// Returns the size in bytes of the memorymap
///
/// \param mem the memorymap to be measured
size_t memorymap_size();

void memorymap_print(memorymap_t* mem);
#endif /* MEMORYMAP_H */
