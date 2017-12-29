#ifndef GC_UTILS_H
#define GC_UTILS_H

#include "gc.h"
#include "cell.h"

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

//returns a cell that contains ptr's address
cell_t* h_get_cell(heap_t* h, void* ptr);

//returns a cell's bump pointer
void* h_get_cell_front_ptr(heap_t* h, cell_t* cell);

//print all cells in heap with their internal info
void h_print_cells(heap_t* h);

#endif /* GC_UTILS_H */
