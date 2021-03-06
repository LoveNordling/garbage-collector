



#include "compact.h"
#include "object.h"
#include "bits.h"


size_t traverse_root(heap_t* h, void* object_pointer, uintptr_t* heap_pointer, memorymap_t* alloc_map)
{
  //puts("found root");
  
  size_t freed_memory = 0;
  if(!object_is_copied(object_pointer))
    {
      void* new_object;
      if(object_is_layout(object_pointer))
        {

          void* traverse_pointer = object_pointer;
          char* s = get_format_string(object_pointer);
          char *counter = s;
          freed_memory += get_object_size(object_pointer);

          while(*counter)

            {
              if(*counter == '*')
                {
                  if(memorymap_adress_is_taken(alloc_map, *(void**)traverse_pointer))
                    {
                      freed_memory += traverse_root(h,(void*)*(void**)traverse_pointer,
                                                    (uintptr_t*)traverse_pointer, alloc_map);
                    }
                }

              traverse_pointer+=sizeof(uintptr_t);
              counter++;

            }
          new_object = h_alloc_struct(h, s);
          free(s);
        }
      else
        {
          size_t size = get_object_size(object_pointer);
          freed_memory += size;
          new_object = h_alloc_data(h, size);
        }
      memorymap_adress_change(alloc_map, object_pointer);
      object_copy(object_pointer, new_object);
      set_forward_address(object_pointer, new_object);
    }
  *heap_pointer = (uintptr_t)get_forward_address(object_pointer); 
  return freed_memory;
}
