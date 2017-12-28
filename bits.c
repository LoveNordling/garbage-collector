#include "bits.h"

bool object_is_copied(void *ptr)
{    
    return lsbs_of_ptr((uintptr_t)ptr) == 2;
}

bool lsbs_are_zero(uintptr_t pointer)
{
  return !(pointer & (size_t)3);
}

//int i = if bit should be 1 or 0
uintptr_t set_bit(uintptr_t num, int bit_no, int fst)
{
    uintptr_t set_num;

    if(fst == 1)
    {
        set_num = num | ( 1 << (bit_no));
    }
    else
    {
        set_num = num & ~( 1 << (bit_no));
    }

    return set_num;
}
uintptr_t lsbs_to_zero(uintptr_t pointer)
{
  return pointer & ~((size_t)3);
}

uintptr_t set_lsbs(uintptr_t pointer, size_t bits)
{
  uintptr_t ptr = lsbs_to_zero(pointer);
  return ptr ^ bits;
}

//Create bitvector by from a string (first bit is 1)
uintptr_t new_bv_layout(char *layout)
{
    char *current = layout;
    int index = 63;

    while(*current)
    {
        if(*current == 'i' || *current == 'f') {
            
        }
    }
    return 0;
}

//Create bitvector from size (first bit is 0)
//compare 9 bits?
// we  can assume that size is smaller than MAX
uintptr_t new_bv_size(size_t bytes)
{
    uintptr_t leftshifted = bytes << 2;
    return set_lsbs(leftshifted, 3);
     
}

//returns the last two bits in a pointer
int lsbs_of_ptr(uintptr_t pointer)
{
    if((pointer & (size_t)3) == (size_t)0) // 
    {
        return 0;
    }
  else if((pointer & (size_t)2) == (size_t)1)
    {
        return 1;
    }
  else if((pointer & (size_t)1) == (size_t)2)
    {
        return 2;
    }
  else
    {
        return 3;
    }
}

uintptr_t pointer_or_not(uintptr_t vector, char c)
{
  switch(c)
    {
    case '*':
      vector = vector << 2;
      return set_lsbs(vector, 3);
    case 'i':
      vector = vector << 2;
      return set_lsbs(vector,1);
    case 'l':
      vector = vector << 2;
      return set_lsbs(vector,1);
    case 'f':
      vector = vector << 2;
      return set_lsbs(vector,1);
    case 'c':
      vector = vector << 2;
      return set_lsbs(vector,1);
    case 'd':
      vector = vector << 2;
      return set_lsbs(vector,1);
    default:
      return vector;
    }
}
