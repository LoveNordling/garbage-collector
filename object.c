#include "object.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct object {
    uintptr_t header; //forward adress efter objektet flyttats
} object_t;
        

#define point_object(p) (((object_t *)p) + 1) //get pointer from header to object
#define point_header(p) (((object_t *)p) - 1) //get pointer from object to header

/* 
 * det skall vara en bit som avger om layoutspecifikationen är en storlek i bytes, eller 
 * om det är en vektor med mer precis layoutinformation.
 * 
 */

/** OBJECT STUFF **/

object_t* new_object(void* ptr, size_t bytes)
{

    /*TODO
     * GET POINTER TO AVAILABLE MEMORY (From where? heap-function?)
     * (in the meantime just allocate on stack)
     * PTR FROM ^ SETS TO HEADER
     * BUMP POINTER IN CELL? 
     * 
     */

    if(ptr != NULL){
        //create new bit-vector with ptr-layout (first bit is 1)
        //change headers metadata pointer to correct bitvector
    } else {
        //create new bit-vector with bytes size (first bit i 0)
        //change headers metadata-ptr to correct ptr/value
    }

    //set last 2 bits in header metadata-ptr to 11

    
     
    return NULL;
}


/** BIT OPERATIONS TODO: bit_operations module **/



//returns the last two bits in a pointer
int lsbs_of_ptr(uintptr_t pointer)
{
  if((pointer & (size_t)3) == (size_t)0)
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

bool lsbs_are_zero(uintptr_t pointer)
{
  size_t integer = 3;
  return !(pointer & integer); 
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

/** PARSER FUNCTIONS **/

size_t char_value(char c)
{
    switch(c)
    {
    case 'i':
        return sizeof(int);
    case 'l':
        return sizeof(long);
    case 'f':
        return sizeof(float);
    case 'c':
        return sizeof(char);
    case 'd':
        return sizeof(double);
    case '*':
        return sizeof(void *);
    default:
        return 0;
    }
}

bool is_number(char c)
{
  return ('0' <= c && c <= '9');
}

size_t format_string_parser(char* layout)
{
    char* current = layout;
    size_t sum = 0;
    while(*current)
      {
          if(is_number(*current)) //checks if *current is number
          {
            int repeats = atoi(current);
            do // we have to move the ptr if number is bigger than 1 digit.
            {
                current++;
            } while(is_number(*current));
            //If *current is '\0' we assume user wants to allocate chars
            char c = *current != '\0' ? *current : 'c'; 
            sum += repeats * char_value(c);
            current++; 
          }
        else
          {
            sum += char_value(*current);
          }
        current++;
      }
    return sum;
}




int main()
{
    
    char layout[] = "32";
    printf("lsbs of ptr %p is %d\n", layout, lsbs_of_ptr((uintptr_t)layout));
    printf("Amount of bytes that need allocating: %lu \n", format_string_parser(layout));
    //printf("Storage size for : %d \n", sizeof(double));

    // Sizeof operator is used to evaluate the size of a variable
    printf("Size of int: %lu bytes\n"
           "Size of long: %lu bytes\n"
           "Size of float: %lu bytes\n"
           "Size of char: %lu bytes\n"
           "Size of double: %lu bytes\n"
           "Size of void *: %lu bytes\n",
           sizeof(int),sizeof(long),sizeof(float),
           sizeof(char), sizeof(double), sizeof(void*));

    return 0;
}
