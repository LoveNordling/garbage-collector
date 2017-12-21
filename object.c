#include "object.h"

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
    char layout[] = "**ii";
    printf("Amount of bytes that need allocating: %lu \n", format_string_parser(layout));
    //printf("Storage size for : %d \n", sizeof(double));

    return 0;
}
