#include "bits.h"


#define PTR_SIZE (sizeof(uintptr_t) == (size_t)4) ? 4 : 8
#define SYS_BIT (PTR_SIZE == 4) ? 32 : 64
#define SIZE_BIT_LENGTH 10 //TODO MAYBE HAVE IND SIZES IF 32 OR 64 BIT SYS ?



int layout_or_sizenumber(uintptr_t value)
{
  uintptr_t comparison  = 1UL << 63;
  //comparison |= 1UL << 63;
  
  if(comparison & value)
    {
      return 1; //1 står för layout
    }
  else
    {
      return 0; //0 står för sizenumber
    }
}

uintptr_t set_msb(uintptr_t num, int bit)
{
  return set_bit(num, 63, bit);
}

bool lsbs_are_zero(uintptr_t pointer)
{
  return !(pointer & (size_t)3);
}

//int i = if bit should be 1 or 0
uintptr_t set_bit(uintptr_t num, int bit_indx, int fst)
{
    uintptr_t set_num;

    if(fst == 1)
    {
        set_num = num | ( 1 << (bit_indx));
    }
    else
    {
        set_num = num & ~( 1 << (bit_indx));
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

uintptr_t bv_size(uintptr_t bv)
{
    //TODO check if bitvektor ??

    uintptr_t size = bv;

    if(layout_or_sizenumber(bv) == 1)
    {
        size = set_msb(size,0) >> (SYS_BIT - SIZE_BIT_LENGTH - 1);
    }
    else
    {
        size = bv >> 2;
    }
    return size;
}

//Create bitvector by from a string (first bit is 1)
uintptr_t new_bv_layout(char *layout)
{
    char *current = layout;
    //int index = SYS_BIT - SIZE_BIT_LENGTH - 2; //todo 52 if 64-bit, 20 if 32-bit

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
