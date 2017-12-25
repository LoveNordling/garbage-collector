#include <stdbool.h>

typedef struct memorymap memorymap_t;

/// Creates a new memorymap
///
/// \param start_of_heap used to to calculate what adress everybool reperesnts.
/// \param heap_size used to determine how big of a stack we are representing.
/// \param min_alloc_size the lowest amount of memory a user is allowed to allocate. heap_size/min_allocsize = number of bools needed to represent the memory
/// \returns: a memorymap containing a bool for each possible allocation in the heap.
memorymap_t* memorymap_new(void * start_of_heap, int heap_size, int min_allocsize);

/// Used to check if space is empty on stack
///
/// \param mem the memorymap to be checked
/// \param adress the adress to be checked

/// \returns: True if adress is taken
bool memorymap_adress_is_taken(memorymap_t* mem, void * adress);


/// Flips the value of the adress in the memorymap
///
/// \param mem the memorymap to be changed
/// \param adress the adress that we are changing
/// \param size the size of the object to be flipped.
/// \returns: True if adress is taken
void memorymap_adreess_change(memorymap_t * mem, void * adress, int size);

void memorymap_print(memorymap_t *mem);
