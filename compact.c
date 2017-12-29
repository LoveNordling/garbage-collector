


#include "compact.h"


//TODO: traverse the heap starting from a root (sprint 3)

void traverse_root(heap_t* h, void* p, uintptr_t* rp)
{
  
  /*
  if(object_is_copied(p))
    {
    }
  else
    {
      char* op = p;
      char* s = object_get_format_string(p);
      while(*s)
        {
          if(*s == '*')
            {
              traverse_root(h, (void*)*(void**)op, (uintptr_t*)op);
            }
          s++;
        }
      void* new_object = h_alloc_struct(h, s);
      object_copy(p, new_object);
      object_set_forwarding_address(p, new_object);
    }
  
  *rp = object_get_forwarding_address(p);
  */
}
