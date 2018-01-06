#include "gc.h"

#include "gc_utils.h"
#include <stdio.h>
#include <malloc.h>
#include <math.h>
#include "root.h"
#include "object.h"
#ifdef _WIN32
#include <windows.h>
void* STACK_START_P;
#endif
#include "cell.h"

typedef struct heap
{
	bool unsafe_stack;
	float gc_threshold;
	size_t size;
	void* data;
	cell_t* cell_array;
	int cell_count;
} heap_t;

#define MIN_HEAP_SIZE sizeof(heap_t) + 1 //TODO FIX
#define MAX_HEAP_SIZE pow(2, 24)

heap_t* h_init(size_t bytes, bool unsafe_stack, float gc_threshold)
{
	//store start of stack (inte superrobust jag vet)
	#ifdef _WIN32
	STACK_START_P = __builtin_frame_address(0);
	#endif

	//wrong argument checks
	if (bytes < MIN_HEAP_SIZE)
	{
		bytes = MIN_HEAP_SIZE;
		printf("minimum heap size is %lu\n", MIN_HEAP_SIZE);
	}
	else if (bytes > MAX_HEAP_SIZE)
	{
		bytes = MAX_HEAP_SIZE;
		printf("maximum heap size is %f\n", MAX_HEAP_SIZE);
	}
	if (gc_threshold < 0)
	{
		gc_threshold = 0;
		printf("threshold must be larger than 0%%\n");
	}
	else if (gc_threshold > 1.0f)
	{
		gc_threshold = 1.0f;
		printf("threshold must be less than 100%%\n");
	}

	//allocate memory for heap and its metadata
	void* p = NULL;
	int result = 0;
        
	#ifdef _WIN32
	p = __mingw_aligned_malloc(bytes, pow(2, 16));
	#else
	result = posix_memalign(&p, pow(2, 16), bytes);
	#endif

	if (p == NULL || result != 0)
	{
		printf("failed to allocate %lu bytes\n", bytes);
		return NULL;
	}

	//zero out memory
	memset(p, 0, bytes);

	//set metadata
	heap_t* hp = p;
	hp->unsafe_stack = unsafe_stack;
	hp->gc_threshold = gc_threshold;

	hp->size = bytes;


	//set data pointer
	char* bp = p;
	hp->data = (void*) (bp + sizeof(heap_t));

	//initialize cell array
	hp->cell_count = (hp->size - sizeof(heap_t)) / (CELL_SIZE + sizeof(cell_t));
	hp->cell_array = (cell_t*) hp->data;
	for (int i = 0; i < hp->cell_count; ++i)
	{
		cell_initialize(&hp->cell_array[i]);
	}

	//move data pointer forward
	bp = hp->data;
	hp->data = (void*) (bp + hp->cell_count * sizeof(cell_t));

	printf("allocated %lu bytes of memory at: %p\n", bytes, hp);

	return hp;
}

void h_delete(heap_t* h)
{
	#ifdef _WIN32
	__mingw_aligned_free(h);
	#else
	free(h);
	#endif
}

void h_delete_dbg(heap_t* h, void* dbg_value)
{
	
}

bool cell_has_space(cell_t* cell, size_t size)
{
  return cell_front_offset(cell) + size < CELL_SIZE;
}


void* h_get_available_space(heap_t* hp, size_t size)
{
  if(h_used(hp) + size > h_size(hp)/2)
    {
      return NULL;
    }
  for(unsigned int i = 0; i < (unsigned int)hp->cell_count; i++)
    {
      cell_t* cell = &hp->cell_array[i];
      if(cell_has_space(cell, size) && cell_is_active(cell))
        {
          cell_activate(cell);
          void* object_pointer = h_get_cell_front_ptr(hp, cell);
          cell_set_front_offset(cell, cell_front_offset(cell) + size);
          return object_pointer;
        }
    }
  for(unsigned int i = 0; i < (unsigned int)hp->cell_count; i++)
    {
      cell_t* cell = &hp->cell_array[i];
      if(cell_has_space(cell, size))
        {
          cell_activate(cell);
          void* object_pointer = h_get_cell_front_ptr(hp, cell);
          cell_set_front_offset(cell, cell_front_offset(cell) + size);
          return object_pointer;
        }
    }
  return NULL;
}

void* h_alloc_struct(heap_t* h, char* layout)
{
  size_t bytes = format_string_parser(layout);
    //FIND AVAILABLE MEMORY LOCATION
  void *cell_ptr = h_get_available_space(h, bytes);
  if(cell_ptr)
    {
      return new_object(cell_ptr, layout, 0);
    }
  else
    {
      h_gc(h);
      return h_alloc_struct(h, layout);
    }
}

void* h_alloc_data(heap_t* h, size_t bytes)
{
    //TODO check if heap got bytes bytes available
    //TODO check if there is bytes available memory in current
    //cell, go to next if not

  void *cell_ptr = h_get_available_space(h, bytes + sizeof(void*));
  if(cell_ptr)
    {
      return new_object(cell_ptr, NULL, bytes);
    }
  else
    {
      h_gc(h);
      return h_alloc_data(h, bytes);
    }
}

void h_flip_cell_states(heap_t* h)
{
  for(int i = 0; i < h->cell_count; i++)
    {
      cell_t* cell = &h->cell_array[i];
      if(cell_is_active(cell))
        {
          cell_initialize(cell);
        }
      else
        {
          cell_activate(cell);
        }
    }
}

size_t h_gc(heap_t* h)
{
  size_t uses = h_used(h);
  h_flip_cell_states(h);
  scan_roots(h, NULL);
  return uses - h_used(h);
}

size_t h_gc_dbg(heap_t* h, bool unsafe_stack)
{
	h->unsafe_stack = unsafe_stack;
	return h_gc(h);
}

//TTODO
size_t h_avail(heap_t* h)
{
	return 0;
}

size_t h_used(heap_t* h)
{
  int sum = 0;
  for(int i = 0; i < h->cell_count; i++)
    {
      sum += cell_front_offset(&(h->cell_array[i]));
    }
  return sum;
}

size_t h_size(heap_t* h)
{
	return h->size;
}

void* h_data(heap_t* h)
{
	return h->data;
}



cell_t* h_get_cell(heap_t* h, void* ptr)
{
	char* start = (char*) h->data;
	char* p = (char*) ptr;

	int span = p - start;
	int i = span / CELL_SIZE;

	return &h->cell_array[i];
}

void* h_get_cell_front_ptr(heap_t* h, cell_t* cell)
{
  
	int i;
	for (i = 0; cell != &h->cell_array[i] && i < h->cell_count; ++i);
        
        return cell_front_ptr(cell, ((char*) h->data) + i * CELL_SIZE);
        //	return cell_front_ptr(&h->cell_array[i], ((char*) h->data) + i * CELL_SIZE);
}

void h_print_cells(heap_t* h)
{
	printf("\nheap size: %u \t cell size: %u\n", (h->size - sizeof(heap_t)), CELL_SIZE);

	for (int i = 0; i < h->cell_count; ++i)
	{
		printf("cell: %d \tregion: %d-%d\t", i, i * CELL_SIZE + ((char*)h->data-(char*)h), (i+1) * CELL_SIZE + ((char*)h->data-(char*)h));
		printf("state: %s \t", cell_is_active(&h->cell_array[i])?"active":"passive");
		printf("bump ptr: %u.%u\n", h_get_cell_front_ptr(h, &h->cell_array[i]), cell_front_offset(&h->cell_array[i]));
	}
}

