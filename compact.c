


#include "compact.h"
#include "object.h"

//TODO: traverse the heap starting from a root (sprint 3)

void traverse_root(heap_t* h, void* p, uintptr_t* rp)
{
  
  
  if(!object_is_copied(p))
    {
      void* new_object;
      if(object_is_layout(p))
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
          new_object = h_alloc_struct(h, s);
        }
      else
        {
          size_t size = get_object_size(p);
          new_object = h_alloc_data(h, size);
        }
      object_copy(p, new_object);
      set_forwarding_address(p, new_object);
    }
  
  *rp = (uintptr_t)get_forwarding_address(p);
  
}
