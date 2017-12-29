#include "bits.h"

#define PTR_SIZE (sizeof(uintptr_t) == (size_t)4) ? 4 : 8
#define SYS_BIT (PTR_SIZE == 4) ? 32 : 64
#define SIZE_BIT_LENGTH 10 //TODO MAYBE HAVE IND SIZES IF 32 OR 64 BIT SYS ?

uintptr_t bv_size(uintptr_t bv)
{
    uintptr_t size = bv;
    /* uintptr_t size;
     * IF BV-BIT == 0
     * size = bv >> 2
     * ELSE 
     * set_msb(bv, 0);
     * size = bv >> (SYS_BIT - SIZE_BIT_LENGTH - 1);
     *return size;
     */
    return size;
}

bool object_is_copied(void *ptr)
{    
    return lsbs_of_ptr((uintptr_t)ptr) == 2;
}

bool lsbs_are_zero(uintptr_t pointer)
{
  return !(pointer & (size_t)3);
}


//int bit = if bit should be 1 or 0
uintptr_t set_bit(uintptr_t num, int bit_indx, int bit)
{
    uintptr_t set_num;

    if(bit == 1)
    {
        set_num = num | ( 1 << (bit_indx));
    }
    else
    {
        set_num = num & ~( 1 << (bit_indx));
    }
    return set_num;
}

uintptr_t set_msb(uintptr_t num, int bit)
{
    return set_bit(num, 63, bit); //TODO depends if 32-bit or 64-bit
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
uintptr_t new_bv_layout(char *layout, size_t bytes)
{
    char *current = layout;
    int index = SYS_BIT - SIZE_BIT_LENGTH - 2; //todo 52 if 64-bit, 20 if 32-bit
    uintptr_t bv = bytes;

    //Depends if 32 or 64 cmp
    // shift so the 10 bits that represents size
    // are at index 62-53(63-bit cmp), alt 30-21(32-bit cmp)

    //TODO depends if 32 or 64-bit
    bv = bv << (SYS_BIT - SIZE_BIT_LENGTH - 1);

    //TODO
    //Support ex 4* (4 pointers)
    while(*current && index > 0)
    {
        if(*current == '*')
        {
            bv = set_bit(bv, index, 1);
        }
        /*else
        {
            //bv = set_bit(bv, index, 0); //maybe not needed 
            }*/
        index--;
    }

    bv = set_msb(bv,1);
    
    return bv;
}

//Create bitvector from size (first bit is 0)
//compare 9 bits?
// we  can assume that size is smaller than MAX
uintptr_t new_bv_size(size_t bytes)
{
    uintptr_t leftshifted = bytes << 2;
    return set_lsbs(leftshifted, 3);
     
}


int layout_or_sizenumber(uintptr_t value)
{
    uintptr_t comparison = 1UL << (SYS_BIT - 1);
    
    if(comparison & value)
    {
        return 1; //1 står för layout
    }
    else
    {
        return 0; //0 står för sizenumber
    }
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

char *bv_to_str(void *ptr){
    uintptr_t bv = (uintptr_t) ptr;

    if(layout_or_sizenumber(bv))
    {
        //int layout_bits = bv_size(bv) / PTR_SIZE;
        //char *str;
    }
    else
    {
        return "r";
    }

    return "";
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

