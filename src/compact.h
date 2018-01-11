/**
 * @file compact.h
 * @author Love Nordling
 * @author Manuel Alexan
 * @date 08 JAN 2018
 * @brief Memory compacting module
 *
 * This module handles the compacting of the heap. In doing so it frees up garbage objects that cannot be reached from the stack. 
 */


#ifndef COMPACT_H
#define COMPACT_H

#include "gc.h"
#include "memorymap.h"



/**
* Traverse an object in the heap and copy it and
* its child objects to free memory blocks
*
* Copied objects will have their root pointers changed
* to their new addresses. This is done with the pointer rp
*
* @param h the heap
* @param root the root to be traversed
* @param rp a pointer to the root
* @param alloc_map a memory allocation map
* @return the number of bytes collected
*/
size_t traverse_root(heap_t* h, void* p, uintptr_t* rp, memorymap_t* alloc_map);


#endif /* COMPACT_H */
