#include <setjmp.h>
#include <stdlib.h>
#include "gc.h"

#define Dump_registers()   \
  jmp_buf env;             \
  if(setjmp(env)) abort(); \


#ifdef _WIN32
#define STACK_GROWS_DOWNWARDS 1
//TODO: kolla åt vilket håll stackminnet växer på linux
#else
#define STACK_GROWS_DOWNWARDS 1       //rätt?
#endif

extern char **environ;

void *stack_get_end()
{
  return __builtin_frame_address(0);
}

void *stack_get_start()
{
  return environ;
}

unsigned int stack_size()
{
  return stack_get_start() - stack_get_end();
}

bool is_valid_pointer(heap_t *heap, int size, void *p)
{
  if(p > (void*)heap && (char*)p < (char*)heap + size)
    {
      return true;
    }
  else
    {
      return false;
    }
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
  void *top = stack_get_end();
  void *p;
  for(int i = 0; i*sizeof(void*) < stack_size(); i += 1)
    {
      if (STACK_GROWS_DOWNWARDS)
        {
          p = top + i;
        }
        else
        {
          p = top - i;
        }
      if(is_valid_pointer(heap, h_size(heap), p))
        {
          heap_traverse(heap, p + i);
        }
    }
}

