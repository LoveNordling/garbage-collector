


#include "compact.h"
#include "object.h"

//TODO: traverse the heap starting from a root (sprint 3)

size_t traverse_root(heap_t* h, void* root, uintptr_t* rp)
{
  
  size_t freed_memory = 0;
  if(!object_is_copied(root))
    {
      void* new_object;
      if(object_is_layout(root))
        {
          char* op = root;
          char* s = get_format_string(root);
          freed_memory += get_object_size(root);
          while(*s)
            {
              if(*s == '*')
                {
                  freed_memory += traverse_root(h, (void*)*(void**)op, (uintptr_t*)op);
                }
              root++;
              s++;
            }
          free(s);
          new_object = h_alloc_struct(h, s);
        }
      else
        {
          size_t size = get_object_size(root);
          freed_memory += size;
          new_object = h_alloc_data(h, size);
        }
      object_copy(root, new_object);
      set_forward_address(root, new_object);
    }
  *rp = (uintptr_t)get_forward_address(root); 
  return freed_memory;
}
