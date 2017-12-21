#include "object.h"
#include <stdbool.h>
#include <stdint.h>

typedef struct object {
    void *data; //forward adress efter objektet flyttats
} object_t;
        
typedef struct header {
    void *ptr; //TODO bitvektor  
} header_t;

//TODO
//#define TO READ AND EDIT LAST TWO BITS

// #define LAST TO BITS TO 0, shift right 2, shift left 2

/** Ligga i egen modul Parser? Kanske lite onödigt. 
 **/

typedef struct object {
    void *data; //forward adress efter objektet flyttats
} object_t;

typedef struct header {
    void *ptr; //TODO bitvektor
} header_t;


bool lsbs_are_zero(uintptr_t pointer)
{
  size_t integer = 3;
  
  return !(pointer & integer); 
}

uintptr_t byte_flipper_to_zero(uintptr_t pointer)
{
  size_t bitstoclear = 3;
    if(lsbs_are_zero(pointer))
        {
          return pointer;
        }
    else
        {
          return pointer = pointer & ~bitstoclear;
        }
    
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

size_t format_string_parser(char* layout)
{
    char* current = layout;
    size_t sum = 0;
    while(*current)
    {
        sum = sum + char_value(*current);
        current++;
    }
  
    return sum;
}




int main()
{
  int x;
  int *num= &x;

    /* Input number from user */
    printf("Enter any number: ");
    scanf("%d", &x);
    printf("%d\n",*num);
    /* If (num & 1) evaluates to 1 */
    if(lsbs_are_zero(*num))
        printf("LSB of %d is unset (0).\n", *num);
    else
        printf("LSB of %d is set (1).\n", *num);

    printf("Original value: %d Flipped number:%d\n",*num, byte_flipper_to_zero(*num));
 

  /*
    char layout[] = "**ii";
    printf("Amount of bytes that need allocating: %lu \n", format_string_parser(layout));
  */
    printf("Storage size for : %d \n", sizeof(unsigned long long));
    
    return 0;
}
