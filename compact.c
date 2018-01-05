


#include "compact.h"
#include "object.h"
#include "bits.h"
//TODO: traverse the heap starting from a root (sprint 3)

size_t traverse_root(heap_t* h, void* p, uintptr_t* rp)
{
  
  size_t freed_memory = 0;
  if(!object_is_copied(p))
    {
      void* new_object;
      if(object_is_layout(p))
        {
          char* op = p;
          char* s = get_format_string(p);
          char* counter = s;
          freed_memory += get_object_size(p);
          while(*counter)
            {
              if(*counter == '*')
                {
                  freed_memory += traverse_root(h, (void*)*(void**)op, (uintptr_t*)op);
                }
              p++;
              counter++;
            }
          
          new_object = h_alloc_struct(h, s);
          free(s);
        }
      else
        {
          size_t size = get_object_size(p);
          freed_memory += size;
          new_object = h_alloc_data(h, size);
        }
      object_copy(p, new_object);
      set_forward_address(p, new_object);
    }
  *rp = (uintptr_t)get_forward_address(p); 
  return freed_memory;
}
