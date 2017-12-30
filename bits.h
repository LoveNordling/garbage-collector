/**
 * @file bits.h
 * @author Elwira Johansson
 * @author Ricardo Danza
 * @date 29 December 2019
 * @brief File containing the functions pertaining bitwise-manipulation.
 *
 * The object.h module relies heavily on bit-manipulations such as setting the least
 * significant bits of a uintptr_t type as well as the most significant bits. The 
 * functions contained here also 
 * The functions here assume that one is sending a bit vector as a parameter to
 * the function. There is no support for sending in structs or pointers.
 * 
 */

#ifndef BITS_H
#define BITS_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <math.h>



/**
 * @brief 
 *
 * @param  
 * @return  
 */
int layout_or_sizenumber(uintptr_t value);

/**
 * @brief 
 *
 * @param  
 * @return  
 */

bool object_is_copied(void *ptr);

/**
 * @brief 
 *
 * @param  
 * @return  
 */
bool lsbs_are_zero(uintptr_t pointer);

/**
 * @brief 
 *
 * @param  
 * @return  
 */
//int i = if bit should be 1 or 0
uintptr_t set_bit(uintptr_t num, int bit_no, int fst);

/**
 * @brief 
 *
 * @param  
 * @return  
 */
uintptr_t bv_size(uintptr_t bv);

/**
 * @brief 
 *
 * @param  
 * @return  
 */
uintptr_t lsbs_to_zero(uintptr_t pointer);

/**
 * @brief 
 *
 * @param  
 * @return  
 */
uintptr_t set_lsbs(uintptr_t pointer, size_t bits);

/**
 * @brief 
 *
 * @param  
 * @return  
 */
//Create bitvector by from a string (first bit is 1)
uintptr_t new_bv_layout(char *layout);

/**
 * @brief 
 *
 * @param  
 * @return  
 */
//Create bitvector from size (first bit is 0)
//compare 9 bits?
// we  can assume that size is smaller than MAX
uintptr_t new_bv_size(size_t bytes);

/**
 * @brief 
 *
 * @param  
 * @return  
 */
//returns the last two bits in a pointer
int lsbs_of_ptr(uintptr_t pointer);

/**
 * @brief 
 *
 * @param  
 * @return  
 */
uintptr_t pointer_or_not(uintptr_t vector, char c);


#endif /* BITS_H */
