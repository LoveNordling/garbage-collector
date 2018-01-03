/**
 * @file object.c
 * @author Ricardo Danza
 * @author Elwira Johansson
 * @date 1 January 2018
 * 
 */

#include "object.h"
#include "bits.h"

//The struct is just the header, the "object" (the data)
//comes after which is accessed by point_object(oject_t *p)
struct object {
    uintptr_t header; 
};

//äöåååååååååååååååååååååååååå¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨äööööööööö
//- comment made by dog, slamming her head on my keyboard

//Get pointer from the object struct/header to the "object" aka the actual data.
#define point_object(p) (((object_t *)p) + 1) 

//Get pointer from the actual data/the pointer the user handles to the actual object struct.
#define point_header(p) (((void *)p) - sizeof(object_t))

//Maximum size on objects(header not included) is set by how big chunk a bit-vector
//can represent
const size_t MAX_OBJECT_SIZE = 240;//(SYS_BIT - SIZE_BIT_LENGTH - 3) * PTR_SIZE; //[[WIP]]

/**
*****************************************************************************
*************************** OBJECT FUNCTIONS ********************************
*****************************************************************************
*/

void* new_object(void* memory_ptr, void* layout, size_t bytes)
{

    object_t *object = memory_ptr;

    //IF layout is not NULL the function is called from h_alloc_struct
    if(layout != NULL)
    {
        object->header = new_bv_layout(layout, bytes);
    }
    //Otherwise it's called from h_alloc_data and only wants to allocate a
    //chunk of data
    else
    {
        object->header = new_bv_size(bytes);
    }
 
    return point_object(object);
}

//Modified var-name on object_t "header" to "obj_struct"
void object_copy(object_t *p, object_t *new_p)
{
    object_t *obj_struct = point_header(p);
    uintptr_t obj_size = bv_size((uintptr_t)obj_struct->header);                          
  
    uintptr_t size = sizeof(obj_struct)+obj_size;
    memcpy(new_p, obj_struct, size);
    obj_struct = point_object(obj_struct);
    set_forward_address(obj_struct, new_p );
 
}

//If header is a forwardadress, the object has been copied.
bool object_is_copied(void *p)
{
    object_t *obj = point_header(p);
    return(get_lsbs(obj->header) == 2);
}

void set_forward_address(object_t *current, void *address)
{
    uintptr_t frw_address = set_lsbs((uintptr_t)address,2);
    object_t *obj = point_header(current);
    obj->header = frw_address;
}

void* get_forward_adress(void *object){
    //TODO
    //CHECK IF FORWARD ADRESS ?
    object_t* obj = point_header(object);
    uintptr_t header = obj->header;

    void* frw_adress = (void *)set_lsbs(header,0);

    return frw_adress;
}

//Gets the size of the object, header not included(maybe should be?),
//aka the data-part the user has access to. 
size_t get_object_size(void *obj){
    object_t *object = point_header(obj);
    return bv_size(object->header);
}

//DO WE NEED THIS?
uintptr_t get_header(void* obj)
{
    object_t *object = point_header(obj);
    return object->header;
}


//NEED COMMENTS
bool object_is_layout(void *obj){
    return get_msb(get_header(obj));
}

char* get_format_string(void *obj){
    uintptr_t bv = get_header(obj);

    return bv_to_str(bv);
}

/**
*****************************************************************************
*************************** PARSER FUNCTIONS ********************************
*****************************************************************************
*/

size_t char_value(char c)
{
    return sizeof(uintptr_t);
}

/* size_t char_value(char c)
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
    } */

bool is_number(char c)
{
  return ('0' <= c && c <= '9');
}

//TODO OPTIMIZE IF STR IS EX "cc*" SHOULD ONLY NEED 16BYTES
//BUT NOW NEEDS 24BYTES
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

/*

MAIN FILE TO TEST/CHECK SOME STUFFS WHILE IMPLEMENTING

int main()
{

  char layout[] = "***";
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
         sizeof(char), sizeof(double), sizeof(void *),
         sizeof(object_t));

  printf("First byte is %d\n", layout_or_sizenumber(bigassbit));

  return 0;
}
*/
