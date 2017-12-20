#include <setjmp.h>
#include <stdlib.h>
#include "gc.h"
/*
#define Dump_registers()   \
  jmp_buf env;             \
  if(setjmp(env)) abort(); \
*/

extern char **environ;

void *stack_get_top()
{
  return __builtin_frame_address(0);
}

void *stack_get_bottom()
{
  return environ;
}

int stack_size()
{
  return stack_get_bottom() - stack_get_top();
}

bool is_valid_pointer(bool map, void *p)
{
  return true;
}

struct header
{
  bool is_copied;
  char *format_string;
};

typedef struct header header_t;


void object_copy(heap_t *heap, void* p)
{

}

void heap_traverse(heap_t *heap, void *p)
{
  
  header_t *header = p - sizeof(header_t);
  if(header->is_copied){
    return;
  }
  char *string = header->format_string;
  while(string)
    {
      p += sizeof(void*);
      if(*string == '*')
        {
          heap_traverse(heap, p);
        }
    }
  object_copy(heap, p);
}

void stack_traverse(heap_t *heap, bool *map)
{
  void *top = stack_get_top();
  for(int i = 0; i < stack_size(); i += sizeof(void*))
    {
      void *p = top + i;
      if(is_valid_pointer(map, p))
        {
          heap_traverse(heap, p + i);
        }
    }
}

