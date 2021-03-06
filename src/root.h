/**
 * @file root.h
 * @author Manuel Alexan
 * @author Love Nordling
 * @date 08 JAN 2018
 * @brief Module for finding pointers to heap
 *
 * The functions in in this module handles the traversal of the program stack, finding pointers in
 * this stack and calling the compact module on these. Thus this module is dependent on compact.h
 * module. 
 */


#ifndef ROOT_H
#define ROOT_H

#include <stdbool.h>
#include <stdint.h>
#include "gc.h"

#include "memorymap.h"
#include "stdint.h"

/**
* Scan the roots of the program and perform a garbage collection
*
* This function will scan the register, stack and static memory 
* of the program and will perform a compaction of alive objects
* on the fly.
*
* @param h the heap
* @param alloc_map the allocation alloc_map
* @return the number of bytes collected
*/
size_t scan_roots(heap_t* h, memorymap_t* alloc_map);

/*
* Calculates the size of the stack memory region
*
* @return the size of the stack in bytes
*/
size_t stack_size();

/*
* Determines if a pointer is within the address range of a heap
*
* @param h the heap
* @param p the pointer
* @return whether it points to the heap
*/
bool is_pointer_to_heap(heap_t* h, void* p);

#endif /* ROOT_H */
