#include "object.h"
#include "bits.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <math.h>
#include <string.h>


struct object {
    uintptr_t header; //forward adress efter objektet flyttats
};

#define point_object(p) (((object_t *)p) + 1) //get pointer from header to object
#define point_header(p) (((object_t *)p) - 1) //get pointer from object to header

const size_t MAX_OBJECT_SIZE = 240;

/* 
 * det skall vara en bit som avger om layoutspecifikationen är en storlek i bytes, eller 
 * om det är en vektor med mer precis layoutinformation.
 * 
 */

/** OBJECT STUFF **/
bool object_is_copied(void *p)
{   
    return(lsbs_of_ptr((uintptr_t)p) == 2);
}


void set_forwarding_address(object_t *current, void *address)
{
    uintptr_t faddress = set_lsbs((uintptr_t)address,2);
    current->header = faddress;
}


void object_copy(object_t *p, object_t *new_p)
{
    object_t *header = point_header(p);
    uintptr_t obj_size = bv_size((uintptr_t)header);                          
  
    uintptr_t size = sizeof(header)+obj_size;Funct
    memcpy(new_p, header, size);
    header = point_object(header);
    set_forwarding_address(header , new_p );
 
}

bool is_number(char c)
{
  return ('0' <= c && c <= '9');
}

void* new_object(void* memory_ptr, void* layout, size_t bytes)
{

    /*TODO
     * GET POINTER TO AVAILABLE MEMORY (From where? heap-function?)
     * (in the meantime just allocate on stack)
     * PTR FROM ^ SETS TO HEADER
     * BUMP POINTER IN CELL?
     * 
     */

    object_t *object = memory_ptr;

    //SET object->header
    if(layout != NULL)
    {
        //create new bit-vector with ptr-layout (first bit is 1)
        //change headers metadata pointer to correct bitvector
        object->header = new_bv_layout(layout);
    }
    else
    {
        //create new bit-vector with bytes size (first bit is 0)
        //change headers metadata-ptr to correct ptr/value
        
        object->header = new_bv_size(bytes);
    }

    //set last 2 bits in header metadata-ptr to 11
 
    return point_object(object);
}

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

//Returns a number wich represents the size of the object.
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


/*

int main()
{
    
  char layout[] = "***";
  uintptr_t ptr = (uintptr_t) layout;
  uintptr_t bigassbit = 1;
  bigassbit |= 1UL << 63;
  printf("lsbs of ptr %p is %d\n", layout, lsbs_of_ptr((uintptr_t)layout));
  printf("Amount of bytes that need allocating: %lu \n", format_string_parser(layout));
  //printf("Storage size for : %d \n", sizeof(double));

  // printbits(ptr);

  // Sizeof operator is used to evaluate the size of a variable
  printf("Size of int: %lu bytes\n"
         "Size of long: %lu bytes\n"
         "Size of float: %lu bytes\n"
         "Size of char: %lu bytes\n"
         "Size of double: %lu bytes\n"
         "Size of void *: %lu bytes\n"
         "Size of object_t: %lu bytes\n",
         sizeof(int),sizeof(long),sizeof(float),
         sizeof(char), sizeof(double), sizeof(void*),
         sizeof(object_t));

  printf("First byte is %d\n", layout_or_sizenumber(bigassbit));

  return 0;
}
*/
