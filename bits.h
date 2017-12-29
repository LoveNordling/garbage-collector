#ifndef BITS_H
#define BITS_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <math.h>

bool object_is_copied(void *ptr);

bool lsbs_are_zero(uintptr_t pointer);

//int i = if bit should be 1 or 0
uintptr_t set_bit(uintptr_t num, int bit_no, int fst);


uintptr_t lsbs_to_zero(uintptr_t pointer);

uintptr_t set_lsbs(uintptr_t pointer, size_t bits);

//Create bitvector by from a string (first bit is 1)
uintptr_t new_bv_layout(char *layout, size_t bytes);

//Create bitvector from size (first bit is 0)
//compare 9 bits?
// we  can assume that size is smaller than MAX
uintptr_t new_bv_size(size_t bytes);

//returns the last two bits in a pointer
int lsbs_of_ptr(uintptr_t pointer);

uintptr_t pointer_or_not(uintptr_t vector, char c);

int layout_or_sizenumber(uintptr_t value);

char* bv_to_str(void *ptr);


#endif /* BITS_H */
