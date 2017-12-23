#include "object.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct object {
    uintptr_t header; //forward adress efter objektet flyttats
} object_t;
        

/* 
 * det skall vara en bit som avger om layoutspecifikationen är en storlek i bytes, eller 
 * om det är en vektor med mer precis layoutinformation.
 * 
 */
typedef struct header {
    uintptr_t ptr; 
} header_t;



//TODO
//#define TO READ AND EDIT LAST TWO BITS

// #define LAST TO BITS TO 0, shift right 2, shift left 2

/** Ligga i egen modul Parser? Kanske lite onödigt. 
 **/

/** OBJECT STUFF **/

header_t* header_ptr(object_t* object){
    return NULL;
}

object_t* object_ptr(header_t* header){
    return NULL;
}

header_t *new_header(size_t bytes){
    return NULL;
}

#define point_object(p) (((object_t *)p) + 1)
#define point_headert(p) (((object_t *)p) -1)

object_t* new_object(void* ptr, size_t bytes){

    /*TODO
     * GET POINTER TO AVAILABLE MEMORY (From where? heap-function?)
     * CREATE HEADER 
     * ASSIGN IT TO PTR
     * OBJECT PTR = HEADER PTR + SIZEOF(HEADER_T) 
     * BUMP POINTER IN CELL? 
     * 
     */


    
    if(ptr != NULL){
        size_t b = format_string_parser(ptr);
        new_header(b);
    } else {
        new_header(bytes);
    }
  
    return NULL;
}





/** BIT OPERATIONS TODO: bit_operations **/

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
            while(is_number(*current)) // we have to move the ptr if number is bigger than 1 digit.
              {
                current++;
              }
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
