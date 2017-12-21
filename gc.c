#include "gc.h"
#include <stdio.h>
#include <malloc.h>
#include <math.h>
#include "cell.h"

#ifdef _WIN32
#include <windows.h>
#endif

#define MIN_HEAP_SIZE 1
#define MAX_HEAP_SIZE pow(2, 24)

typedef struct heap
{
  bool unsafe_stack;
  float gc_threshold;
  void* data;
  size_t size;
  size_t cell_size;
} heap_t;

heap_t* h_init(size_t bytes, bool unsafe_stack, float gc_threshold)
{
	//wrong argument checks
	if (bytes < MIN_HEAP_SIZE)
	{
		bytes = MIN_HEAP_SIZE;
		printf("minimum heap size is %d\n", MIN_HEAP_SIZE);
	}
	if (bytes > MAX_HEAP_SIZE)
	{
		bytes = MAX_HEAP_SIZE;
		printf("maximum heap size is %d\n", MAX_HEAP_SIZE);
	}
	if (gc_threshold < 0)
	{
		gc_threshold = 0;
		printf("threshold must be larger than 0%%\n");
	}
	if (gc_threshold > 1.0f)
	{
		gc_threshold = 1.0f;
		printf("threshold must be less than 100%%\n");
	}

	//allocate memory for heap and its metadata
	int b = bytes + sizeof(heap_t);
	void* p = NULL;
	int result = 0;
        size_t size = b;
	#ifdef _WIN32
	p = __mingw_aligned_malloc(b, pow(2, 16));
	#else
	result = posix_memalign(&p, pow(2, 16), b);
	#endif

	if (p == NULL || result != 0)
	{
		printf("failed to allocate %d bytes\n", b);
		return NULL;
	}

	//zero out memory
	memset(p, 0, b);

	//set struct pointer
	heap_t* hp = p;
	hp->unsafe_stack = unsafe_stack;
	hp->gc_threshold = gc_threshold;

	//set heap pointer
	char* bp = p;
	hp->data = bp + sizeof(heap_t);
        hp->size = size;

        //init cells
        hp->cell_size = 200;
        
        for( void* cell = hp->data; cell < (void*)(hp + size); cell += (hp->cell_size + sizeof(cell)))
          {
            cell_new(cell);
          }
        for( void* cell = hp->data; cell < (void*)(hp + size); cell += (hp->cell_size + sizeof(cell)))
          {
            printf("%s ", cell_is_active(cell) ? "true" : "false");
          }
	printf("allocated %d bytes of memory at: %d\n", b, hp);

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


void* h_alloc_struct(heap_t* h, char* layout)
{
	return NULL;
}

void* h_alloc_data(heap_t* h, size_t bytes)
{
	return NULL;
}


size_t h_gc(heap_t* h)
{
	return 0;
}

size_t h_gc_dbg(heap_t* h, bool unsafe_stack)
{
	return 0;
}

size_t h_avail(heap_t* h)
{
	return 0;
}

size_t h_used(heap_t* h)
{
	return 0;
}

size_t h_size(heap_t *h)
{
  return h->size;
}
