/**
 * @file compact.h
 * @author Manuel Alexan
 * @author Love Nordling
 * @date 10 January 2018
 * @brief 
 *
 * 
 */

#ifndef COMPACT_H
#define COMPACT_H

#include "gc.h"
#include "memorymap.h"


/**
 * @brief Traverse an object in the heap and copy it and
 * its child objects to free memory blocks
 *
 * Copied objects will have their root pointers changed
 * to their new addresses. This is done with the pointer rp
 *
 * @param h the heap
 * @param root the root to be traversed
 * @param rp a pointer to the root
 * @return the number of bytes collected
 */
size_t traverse_root(heap_t* h, void* object_pointer, uintptr_t* heap_pointer, memorymap_t* alloc_map);

#endif /* COMPACT_H */
