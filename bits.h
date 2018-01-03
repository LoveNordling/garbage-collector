/**
 * @file bits.h
 * @author Elwira Johansson
 * @author Ricardo Danza
 * @date 1 January 2018
 * @brief File containing the functions pertaining bitwise-manipulation.
 *
 * The object.h module relies heavily on bit-manipulations such as setting the least
 * significant bits of a uintptr_t type as well as the most significant bits. The 
 * functions contained here also assume that one is sending a bit vector as a parameter to
 * the function. There is no support for sending in structs or pointers. 
 *
 * When creating a bit-vector the functions always assume that the byte-size param is always
 * less than max_size ie that size can be represented by SIZE_BIT_LENGTH bits. 
 * 
 */

#ifndef BITS_H
#define BITS_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

#define PTR_SIZE (sizeof(uintptr_t) == (size_t)4) ? 4 : 8
#define SYS_BIT (PTR_SIZE == 4) ? 32 : 64
#define SIZE_BIT_LENGTH  10 //TODO CALCULATE APPROPRIATE BIT FOR 32-BIT SYS




void print_bits(uintptr_t uintbits);

/**
*********************************************************************************
*************************** PRINT UINTPTR_T FUNC ********************************
*********************************************************************************
*/

void print_bits(uintptr_t uintbits);

/**
*********************************************************************************
*************************** BIT-VECTOR FUNCTIONS ********************************
*********************************************************************************
*/

/**
 * @brief Creates a new bit-vector layout from a format-string.
 * MSB is always set to 1 when bit-vector is a layout-format.
 *
 * @param layout The format-string
 * @param bytes The size of the struct in bytes which the format-string represents.
 * @return The bit-vector layout in correct format.
 */
uintptr_t new_bv_layout(char *layout, size_t bytes);

/**
 * @brief Creates a new bit-vector with size only.
 * If the bit-vector is size only, it only represents a chunk
 * of data, ie no pointers.
 * MSB is always set to 0 when bit-vector is a size only.
 *
 * @param bytes The size of the data-chunk the bit-vector should represent
 * @return The bit-vector with the size. 
 */
uintptr_t new_bv_size(size_t bytes);

/**
 * @brief Calculates the size of a bit-vector
 * Doesn't matter if it's a bv-layout or bv-size.
 *
 * @param bv The bit-vector 
 * @return The size of bit-vector bv in bytes.
 */
uintptr_t bv_size(uintptr_t bv);

/**
 * @brief Parsers a bit-vector to a simplified format-string
 *
 * Pointers are represented by '*' and all other non-pointers
 * are represented by 'r'.
 *
 * @param bv The bit-vector to be parsed
 * @return The simplified format-string
 */
char* bv_to_str(uintptr_t bv);

/**
*********************************************************************************
************************ BIT-MANIPULATION FUNCTIONS *****************************
*********************************************************************************
*/

/**
 * @brief Sets a bit at index bit_index to either 1 or 0.
 *
 * MSB is represented by bit_index = SYS_BIT - 1
 * LSB is represented by bit_index = 0
 *
 * @param num The uintptr_t that is to be modified
 * @param bit_index The index of the bit that is to be set 
 * @param bit What value the bit should be set to
 * @return A modified num with value bit at index bit_index
 */
uintptr_t set_bit(uintptr_t num, int bit_index, int bit);

/**
 * @brief Sets the least 2 significants bits to the requested value
 *
 * Expected values of bits:
 * - (size_t) 0, sets lsbs to 00
 * - (size_t) 1, sets lsbs to 01
 * - (size_t) 2, sets lsbs to 10
 * - (size_t) 3, sets lsbs to 11
 *
 * @param pointer The pointer to be modified
 * @param bits The requested value of the lsbs
 * @return The modified pointer
 */
uintptr_t set_lsbs(uintptr_t pointer, size_t bits);

/**
 * @brief Get the least 2 significant bits as an integer value
 *
 * Possible lsbs returns:
 * - 00, returns 0
 * - 01, returns 1
 * - 10, returns 2
 * - 11, returns 3
 *
 * @param pointer
 * @return The value as an integer
 */
int get_lsbs(uintptr_t pointer);

/**
 * @brief Sets the least 2 significant bits to zero
 *
 * @param pointer The uintptr_t that is to be modified
 * @return pointer with last 2 bits set to 00
 */
uintptr_t lsbs_to_zero(uintptr_t pointer);

/**
 * @brief Checks if the least 2 significant bits are zero
 *
 * @param pointer The header member from the object struct
 * @return bool TRUE if last 2 bits are 00, else FALSE
 */
bool lsbs_are_zero(uintptr_t pointer);

/**
 * @brief Function to set most significant bit to value bit
 *
 * @param ptr The pointer to be modified
 * @param bit The requested value of the bit
 * @return ptr with msb set to 1 if bit is 1, otherwise set to 0
 */
uintptr_t set_msb(uintptr_t ptr, int bit);

/**
 * @brief Function to get the most significant bit
 *
 * @param value The pointer to be checked
 * @return 1 if msb is 1, otherwise 0
 */
int get_msb(uintptr_t value);

/**
************************ TODO CHECK IF NEEDED ******************************/

/**
 * @brief 
 *
 * @param  
 * @return  
 */
uintptr_t pointer_or_not(uintptr_t vector, char c);

/**
 * @brief 
 *
 * @param  
 * @return  
 */
bool is_frw_adress(uintptr_t header);

#endif /* BITS_H */
