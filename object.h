/**
 * @file object.h
 * @author Elwira Johansson
 * @author Ricardo Danza
 * @date 29 December 2017
 * @brief Object manipulation module
 *
 * The functions in this module handle the objects created in the allocated heap. They
 * include functions to move an object in the allocated memory, reading and interpreting
 * string parsers, setting forwarding addresses and creating a new object. This module 
 * is dependent on the bits.h module in order to function.
 */

#ifndef OBJECT_H
#define OBJECT_H

#include <stdbool.h>
#include <stdio.h>

/**
 * @brief Contains the header to the object that is placed in the allocated memory.
 *
 * This struct object is always placed immediately before the data that the user saves in
 * the heap. The header in the struct is the size of a pointer 8 bytes in 64bit machines
 * and 4 bytes in a 32bit machine. 
 */
typedef struct object object_t;

/**
 * @brief Gets a memory pointer to a point in memory where the object should be 
 *palced . Creates an object struct, i.e. a header, that is placed immediately 
 *before the beginning of the object. A bit vector is created and stored in the header
 *with information about the layout and/or the size of the object.
 * 
 * @param memory_ptr The location in memory where the object is to be stored 
 * @param layout A format string. 
 * @param bytes The size that the object should have. 
 * @return A pointer to the object that has been placed in the heap.
 */
void* new_object(void* memory_ptr, void* layout, size_t bytes);

/**
 * @brief Creates a copy of the object at another place in the memory
 * Description
 * @param p Pointer to the current location of the object.
 * @param new_p Pointer to the location in memory where the object should be moved to.
 * @return void
 */

void object_copy(object_t *p, object_t *new_p);

/**
 * @brief Checks the first member of the object struct to confirm if the object has been
 * copied.
 * 
 * Note that the pointer should be pointing to the object i.e. the data and not the 
 * object struct.
 *
 * @param p Pointer to the object
 * @return bool 
 */
bool object_is_copied(void *p);


/**
 * @brief Inserts a pointer in the header field of the object_t struct.
 * Said pointer represents the address where the object has been moved to in the heap.
 * 
 * @param current The address of the current object.
 * @param address The destination address where the object is to be copied to.
 * @return void
 */
void set_forwarding_address(object_t *current, void *address);

/**
 * @brief Creates a copy of the object at another place in the memory
 * 
 * @param p Pointer to the current location of the object.
 * @param new_p Pointer to the location in memory where the object should be moved to.
 * @return void
 */
void* get_forwarding_address(object_t *current);

/**
 * @brief Gets the size of an object
 *
 * Does not include size of header, but maybe should?

 * @param obj Pointer to the object
 * @return size_t The size in bytes
 */
size_t get_object_size(void *obj);

/**
 * @brief Reads a format string and calculates the amount of byte the object requires 
 *
 * @param   layout The format string.
 * @return  unsigned int with the size required for the object.
 */
size_t format_string_parser(char* layout);

#endif /* OBJECT_H */
