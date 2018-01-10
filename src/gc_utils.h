/**
 * @file gc_utils.h
 * @author Manuel Alexan
 * @author Love Nordling
 * @date 10 January 2018
 * @brief 
 *
 *  
 * 
 */

#ifndef GC_UTILS_H
#define GC_UTILS_H

#include "gc.h"
#include "cell.h"
/**
 * @brief Returns the size of the heap
 * 
 * @param h the heap
 * @return the size in bytes
 */
size_t h_size(heap_t* h);

/**
 * @brief Returns a pointer to the beginning of the heap's
 * allocated memory block
 *
 * @param h the heap
 * @return the start of the heap's data segment
 */
void* h_data(heap_t* h);

/**
 * @brief Returns a cell that contains ptr's address
 *
 * @param h the heap
 * @param ptr the pointer
 * @return the cell that is pointed to by ptr
 */
cell_t* h_get_cell(heap_t* h, void* ptr);

/**
 * @brief Returns a cell's front pointer
 *
 * @param h the heap
 * @param cell the cell
 * @return the cell's front pointer
 */
void* h_get_cell_front_ptr(heap_t* h, cell_t* cell);

/**
 * @brief Print all cells in the heap with their internal info
 *
 * @param h the heap
 */
void h_print_cells(heap_t* h);

#endif /* GC_UTILS_H */
