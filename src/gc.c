#include "gc.h"

#include "gc_utils.h"
#include "memorymap.h"
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
#include "bits.h"

typedef struct heap
{
	bool unsafe_stack;
	float gc_threshold;
	size_t size;
	void* data;
	cell_t* cell_array;
        memorymap_t* mem;
	int cell_count;
} heap_t;

#define MIN_HEAP_SIZE sizeof(heap_t) + 1 //TODO FIX
#define MAX_HEAP_SIZE pow(2, 24)


size_t check_bad_bytes(size_t bytes)
{
  //wrong argument checks
  if (bytes < MIN_HEAP_SIZE)
    {
      printf("minimum heap size is %lu\n", MIN_HEAP_SIZE);
      return MIN_HEAP_SIZE;
    }
  else if (bytes > MAX_HEAP_SIZE)
    {
      printf("maximum heap size is %f\n", MAX_HEAP_SIZE);
      return MAX_HEAP_SIZE;
    }
  return bytes;
}

float check_bad_threshold(float threshold)
{
  if (threshold < 0)
    {
      printf("threshold must be larger than 0%%\n");
      return 0;
    }
  else if (threshold > 1.0f)
    {
      printf("threshold must be less than 100%%\n");
      return 1.0f;
    }
  return threshold;
}

void init_metadata(heap_t* hp, bool unsafe_stack, float gc_threshold, size_t bytes)
{
//set metadata

	hp->unsafe_stack = unsafe_stack;
	hp->gc_threshold = gc_threshold;

	hp->size = bytes-sizeof(heap_t);
        size_t cell_size = CELL_SIZE;
        hp->size = hp->size - hp->size%cell_size;
        //(bytes-memorymap_size())*CELL_SIZE*sizeof(uintptr_t)/(CELL_SIZE*sizeof(uintptr_t) + sizeof(uintptr_t)+ CELL_SIZE);//Must change if bit vectors are used
}

void init_memmap_and_cellarray(heap_t* hp)
{
  //Initialise memmap
  size_t memmap_size = hp->size/8;
  hp -> mem = memorymap_new(NULL, memmap_size, malloc(memorymap_size() + memmap_size));
  /*
  size_t mem_size  = hp->size/sizeof(uintptr_t) + memorymap_size();
  hp -> data += mem_size;
  */

  //initialize cell array
  hp->cell_count = hp->size/CELL_SIZE;
  hp->cell_array = malloc(sizeof(cell_t)*(hp->cell_count));
  for (int i = 0; i < hp->cell_count; ++i)
    {
      cell_initialize(&hp->cell_array[i]);
    }

  //move data pointer forward
  //hp->data += hp->cell_count * sizeof(cell_t);

  memorymap_set_startofheap(hp -> mem, hp -> data);
}


heap_t* h_init(size_t bytes, bool unsafe_stack, float gc_threshold)
{
	//store start of stack (inte superrobust jag vet)
	#ifdef _WIN32
	STACK_START_P = __builtin_frame_address(0);
	#endif
        bytes = check_bad_bytes(bytes);
	
	gc_threshold = check_bad_threshold(gc_threshold);

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

        //Set metadata
        heap_t* hp = p;
        init_metadata(hp, unsafe_stack, gc_threshold, bytes);
	

	//set data pointer
	hp->data = (void*)hp + sizeof(heap_t);

        //Init memory map and cells of cellarray
        init_memmap_and_cellarray(hp);
        
	printf("allocated %lu bytes of memory at: %p\n", bytes, hp);

	return hp;
}

void h_delete(heap_t* h)
{
  free(h->cell_array);
  free(h->mem);
	#ifdef _WIN32
	__mingw_aligned_free(h);
	#else
	free(h);
	#endif
}

void h_delete_dbg(heap_t* h, void* dbg_value)
{
	
}

//Returns true if cell can fit an object of size size, flase otherwise
bool cell_has_space(cell_t* cell, size_t size)
{
  return cell_front_offset(cell) + size <= CELL_SIZE;
}

//Returns a pointer to the heap where an object of size size can be allocated
//Returns NULL if heap is full
void* h_get_available_space(heap_t* hp, size_t size)
{
  //Check if heap is full
  if(h_used(hp) + size > h_size(hp)/2)
    {
      return NULL;
    }
  //Attempt to allocate only on current active cells
  for(unsigned int i = 0; i < (unsigned int)hp->cell_count; i++)
    {
      cell_t* cell = &hp->cell_array[i];
      if(cell_is_active(cell) && cell_has_space(cell, size))
        {
          void* object_pointer = h_get_cell_front_ptr(hp, cell);
          cell_set_front_offset(cell, cell_front_offset(cell) + size);
          return object_pointer;
        }
    }
  //Allocate on first cell that has space
  for(unsigned int i = 0; i < (unsigned int)hp->cell_count; i++)
    {
      cell_t* cell = &hp->cell_array[i];
      if(cell_has_space(cell, size))
        {
          if((int)i > hp->cell_count/2)
            {
              printf("activating cell %i \n", i);
            }
          cell_initialize(cell);
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
  void *cell_ptr = h_get_available_space(h, bytes + get_header_size());
  if(cell_ptr)
    {
      void* obj = new_object(cell_ptr, layout, bytes);
      memorymap_adress_change(h->mem, obj);
      return obj;
    }
  else
    {
      h_gc(h);
      return h_alloc_struct(h, layout);
    }
}



void* h_alloc_data(heap_t* h, size_t bytes)
{
    void *cell_ptr = h_get_available_space(h, bytes + get_header_size());
  if(cell_ptr)
    {
      void* obj = new_object(cell_ptr, NULL, bytes); 
        memorymap_adress_change(h->mem, obj);
        return obj;
    }
  else
    {
      h_gc(h);
      return h_alloc_data(h, bytes);
    }
}

char *h_strdup(heap_t *h, const char* str)
{
    int len = 0;
    const char *current = str;

    while(*current)
    {
        len++;
        current++;
    }

    char *duped_str = h_alloc_data(h, (size_t)(len+1));

   for (int i = 0; i <= len; i++) {
       duped_str[i] = str[i];
   }

   return duped_str;
}


//Flips the state of every cell and moves the front offset to zero for deactivated cells. 
void h_flip_cell_states(heap_t* h)
{
  for(int i = 0; i < h->cell_count; i++)
    {
      cell_t* cell = &h->cell_array[i];
      if(cell_is_active(cell))
        {
          cell_deactivate(cell);
        }
      else
        {
          cell_initialize(cell);
          cell_activate(cell);
        }
    }
}

size_t h_gc(heap_t* h)
{
  size_t uses = h_used(h);
  h_flip_cell_states(h);
  scan_roots(h, h->mem);
  memorymap_update(h->mem, h->cell_array, h->cell_count);
  printf("Freed %lu bytes\n", uses - h_used(h));
  return uses - h_used(h);
}


size_t h_gc_dbg(heap_t* h, bool unsafe_stack)
{
	h->unsafe_stack = unsafe_stack;
	return h_gc(h);
}

//Returns the amount of available memory
size_t h_avail(heap_t* h)
{
  return h_size(h) - h_used(h);
}

//Returns the amount of allocated memory on the heap
size_t h_used(heap_t* h)
{
  int sum = 0;
  cell_t* cell_array = h->cell_array;
  for(int i = 0; i < h->cell_count; i++)
    {
      size_t offset = cell_front_offset(&(cell_array[i]));
      if(offset)
        {
        
          sum += offset + 1;
        }
    }
  return sum;
}

//returns the total allocable space on the heap
size_t h_size(heap_t* h)
{
	return h->size;
}

//Returns the data pointer for the heap
void* h_data(heap_t* h)
{
	return h->data;
}

//Returns a pointer to the strukt of the cell that ptr is pointing at
cell_t* h_get_cell(heap_t* h, void* ptr)
{
	char* start = (char*) h->data;
	char* p = (char*) ptr;

	int span = p - start;
	int i = span / CELL_SIZE;

	return &h->cell_array[i];
}

//Returns a pointer to where memory can be allocated on cell
void* h_get_cell_front_ptr(heap_t* h, cell_t* cell)
{
	int i;
        //i = (cell - h->cell_array)/sizeof(cell_t);
        //i = h->cell_count - (((size_t)(h->data))-(size_t)cell)/sizeof(cell_t);
                
	for (i = 0; cell != &h->cell_array[i] && i < h->cell_count; ++i);

	return cell_front_ptr(cell, ((char*) h->data) + i * CELL_SIZE);
}


//Prints heap size, cell locations
void h_print_cells(heap_t* h)
{
	printf("\nheap size: %u \t cell size: %u\n", (h->size - sizeof(heap_t)), CELL_SIZE);

	for (int i = 0; i < h->cell_count; ++i)
	{
		printf("cell: %d \tregion: %d-%d\t", i, i * CELL_SIZE + ((char*)h->data-(char*)h), (i+1) * CELL_SIZE + ((char*)h->data-(char*)h));
		printf("state: %s \t", cell_is_active(&h->cell_array[i]) ? "active" : "passive");
		printf("bump ptr: %u.%u\n", h_get_cell_front_ptr(h, &h->cell_array[i]), cell_front_offset(&h->cell_array[i]));
	}
}
