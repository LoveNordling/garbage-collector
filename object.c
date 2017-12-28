#include "object.h"
#include "bits.h"


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

/** PARSER FUNCTIONS **/

/*
  object_copy(p, new_object);  kopierar från p till new_object
  object_set_forwarding_address(p, new_object); 
  Skulle behöva de här funktionerna till kompakteringen
  bool object_is_copied(p)
  char* object_get_format_string(p);

  void object_copy(p, new_object);  kopierar från p till new_object
  void object_set_forwarding_address(p, new_object);
  get_format_string ger en sträng t.ex. "uu"
 */

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

size_t format_string_to_layout(char* format_str)
{
    uintptr_t layout = 0; 
    char* current = format_str;
    size_t sum = 0;
    size_t tracker = 0;
    while(*current)
      {
          if(is_number(*current)) //checks if *current is number
          {
            //check what comes after and write the necessary number of 11's or 01's
            int repeats = atoi(current);
            do // we have to move the ptr if number is bigger than 1 digit.
            {
                
                current++;
            } while(is_number(*current));
            //If *current is '\0' we assume user wants to allocate chars
            char c = *current != '\0' ? *current : 'c'; 
            current++;  //måste göra så att den har stöd för tex "23*i"
          }
        else
          {
            //Bygger en layoutbitvektor om man bara har chars.
           layout = pointer_or_not(layout, *current);
          }
        current++;
      }
    //den måste, när den är klar, flytta talen längst till vänster mha tracker
    //och flippa de sista bitarna.
    return layout;
}

size_t format_string_parser(char* layout)
{
    char* current = layout;
    size_t sum = 0;
    while(*current) //*current != '\0' 
      {
          if(is_number(*current)) //checks if *current is number
          {
              int repeats = atoi(current); //number at current pointer
            do // we have to move the ptr if number is more than 1 digit.
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
    
    char layout[] = "***";
    uintptr_t ptr = (uintptr_t) layout;
    printf("lsbs of ptr %p is %d\n", layout, lsbs_of_ptr(ptr));
    printf("Amount of bytes that need allocating: %lu \n", format_string_parser(layout));
    //printf("Storage size for : %d \n", sizeof(double));

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

    return 0;
}
