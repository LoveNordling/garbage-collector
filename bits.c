#define _GNU_SOURCE
//needed because of strdup and std=c99
//Solution found at: https://gist.github.com/emilisto/9620134

#include "bits.h"
#include <stdio.h>

#define PTR_SIZE (sizeof(uintptr_t) == (size_t)4) ? 4 : 8
#define SYS_BIT (sizeof(uintptr_t) == (size_t)4) ? 32 : 64
#define SIZE_BIT_LENGTH (sizeof(uintptr_t) == (size_t)4) ? 5 : 10 //TODO CALCULATE APPROPRIATE BIT FOR 32-BIT SYS

/* #define PTR_SIZE 8 */
/* #define SYS_BIT 64 */
/* #define SIZE_BIT_LENGTH 10 //TODO CALCULATE APPROPRIATE BIT FOR 32-BIT SYS */


/**
 * @file bits.c
 * @author Elwira Johansson
 * @author Ricardo Danza
 * @date 1 January 2018
 * 
 */

/**
*********************************************************************************
*************************** PRINT UINTPTR_T FUNC ********************************
*********************************************************************************
*/

void print_bits(uintptr_t uintbits)
{
    printf("%lu in bits are: ", uintbits);
    for(int i = SYS_BIT; i > 0; i--){

        uintptr_t comparison = 1UL << (i-1);
    
        if(comparison & uintbits)
        {
            printf("1"); 
        }
        else
        {
            printf("0");
        }
        
    }
    printf("\n\n");
}


/**
*********************************************************************************
*************************** BIT-VECTOR FUNCTIONS ********************************
*********************************************************************************
*/

//

//Create bitvector layout from a string 
uintptr_t new_bv_layout(char *layout, size_t bytes)
{
    int test = SYS_BIT;
    test-=SIZE_BIT_LENGTH;
    char *current = layout;
    int index = test- 2;
    uintptr_t bv = bytes;

    printf("bv before shifting:");
    print_bits(bv);
    //Shift it left so the second msb is the start of bv_size.
    
    //bv = bv << (SYS_BIT - SIZE_BIT_LENGTH - 1);
    bv = bv << test;
    
    printf("SYS_BIT: %d, SIZE_BIT_LENGTH: %d, test: %d \n\n", SYS_BIT, SIZE_BIT_LENGTH, test);

    test = SYS_BIT - SIZE_BIT_LENGTH;
    printf("SYS_BIT: %d, SIZE_BIT_LENGTH: %d, test: %d \n\n", SYS_BIT, SIZE_BIT_LENGTH, test);
    printf("bv after shifting %d:", test);
    print_bits(bv);

    while(*current && index > 0)
    {
        //How many of next char is going to be written in bv
        int repeats = 1;

        //Check if *current is a number EX if str "4*if"
        if('0' <= *current && *current <= '9') 
        {
            
            //number at current pointer
            repeats = atoi(current); 

            // we have to move the ptr current if number is more than 1 digit.
            //EX the str "32c"
            do 
            {
                current++;
            } while('0' <= *current && *current <= '9');
        }

         //If it's a '*' we have to add 'repeats' nr of 1's in bv
        if(*current == '*'){
            do
            {
                bv = set_bit(bv, index, 1);
                printf("Set bit at index %d to 1 with %d repeats!\n", index, repeats);
                print_bits(bv);
                index--;
                repeats--;
            }while(repeats > 0);
        }
        //Else we have to skip 'repeats' nr of 0's if *current =! '*'
        else
        {
            index -= repeats;
        }
        
        current++;
    }

    //MSB shall be 1 if bv is a layout
    bv = set_msb(bv,1);
    print_bits(bv);

    //Return it with lsbs set to 11 since it's a bitvector.
    bv = set_lsbs(bv, 3);
    print_bits(bv);
    return bv;
}

//Create bitvector from size
//we can assume that size is smaller than MAX
uintptr_t new_bv_size(size_t bytes)
{
    //Shift it to left by 2 so we can fits 2 lsbs as metadata.
    uintptr_t leftshifted = bytes << 2;
    
     //Return it with lsbs set to 11 since it's a bitvector.
    return set_lsbs(leftshifted, 3);
}

uintptr_t bv_size(uintptr_t bv)
{
    //TODO check if bitvektor ??
    
    uintptr_t size = bv;

    if(get_msb(bv) == 1)
    {
        size = set_msb(size,0);
        size = size >> (SYS_BIT - SIZE_BIT_LENGTH - 1);
    }
    else
    {
        size = bv >> 2;
    }
    return size;
}

//Function to create a simplified format-str from a bv
//1 = pointer, 0 = non-pointer
char *bv_to_str(uintptr_t bv){

    if(get_msb(bv) == 1)
    {
        int ptr_size = PTR_SIZE;
        int layout_bits = bv_size(bv) / ptr_size; //Why can I not divide by a defined?
        
        char str[layout_bits + 1];
        uintptr_t comp = 1UL << (SYS_BIT - SIZE_BIT_LENGTH - 1);

        //loop to create the string.
        for(int i = 0; i < layout_bits; i++, comp = comp << 1)
        {
            if(bv & comp)
            {
                str[i] = '*';
            }
            else
            {
                str[i] = 'r';
            }
        }
        str[layout_bits] = '\0';
        return strdup(str);
    }
    else
    {
        return strdup("r");
    }
}

/**
*********************************************************************************
************************ BIT-MANIPULATION FUNCTIONS *****************************
*********************************************************************************
*/

// Function to set a bit in uintptr_t num
// Returns num with the new value bit at index bit_indx
uintptr_t set_bit(uintptr_t num, int bit_index, int bit)
{
    uintptr_t set_num;

    if(bit == 1)
    {
        set_num = num | ( 1UL << (bit_index));
        print_bits(set_num);
    }
    else
    {
        set_num = num & ~( 1UL << (bit_index));
        print_bits(set_num);
    }
    return set_num;
}

//Function to set lsbs to given bit-pair
// bits can be called with:
// - (size_t) 0 (sets lsbs to bits 00)
// - (size_t) 1 (sets lsbs to bits 01)
// - (size_t) 2 (sets lsbs to bits 10)
// - (size_t) 3 (sets lsbs to bits 11)
uintptr_t set_lsbs(uintptr_t pointer, size_t bits)
{
  uintptr_t ptr = lsbs_to_zero(pointer);
  return ptr ^ bits;
}

//returns the value of the last two bits in a pointer
int get_lsbs(uintptr_t pointer)
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

// Function to set lsbs to zero
uintptr_t lsbs_to_zero(uintptr_t pointer)
{
  return pointer & ~((size_t)3);
}

//Function to check if lsbs are zero
bool lsbs_are_zero(uintptr_t pointer)
{
  return !(pointer & (size_t)3);
}

//Function to set msb to bit (IF 1, SETS TO 0, ELSE SETS TO 0)
uintptr_t set_msb(uintptr_t num, int bit)
{
    return set_bit(num, SYS_BIT-1, bit); 
}

//Checks if bv is a layout or just a size
//This function shall always be called with a checked-bv
int get_msb(uintptr_t value)
{
    uintptr_t comparison = 1UL << (SYS_BIT - 1);
    
    if(comparison & value)
    {
        return 1; 
    }
    else
    {
        return 0; 
    }
}


/**
************************ TODO CHECK IF NEEDED ****************************
*/
//If header's 2 lsbs are 10 the header is a forward adress 
bool is_frw_adress(uintptr_t header)
{    
    return get_lsbs(header) == 2;
}

//TODO ASK
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

