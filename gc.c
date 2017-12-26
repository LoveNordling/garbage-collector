#include "gc.h"
#include "object.h"

#define MIN_HEAP_SIZE sizeof(heap_t) + 4 
#define MAX_HEAP_SIZE pow(2, 24)

typedef struct heap
{
    bool unsafe_stack;
    float gc_threshold;
    void* data;
    size_t size;
} heap_t;

heap_t* h_init(size_t bytes, bool unsafe_stack, float gc_threshold)
{
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

	//set struct pointer
	heap_t* hp = p;
	hp->unsafe_stack = unsafe_stack;
	hp->gc_threshold = gc_threshold;
        hp->size = bytes - sizeof(heap_t);

	//set heap pointer
	char* bp = p;
	hp->data = bp + sizeof(heap_t);

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


void* h_alloc_struct(heap_t* h, char* layout)
{
    //FIND AVAILABLE MEMORY LOCATION
    void *cell_ptr = NULL;
    return new_object(cell_ptr, layout, 0);
}

void* h_alloc_data(heap_t* h, size_t bytes)
{
    //TODO check if heap got bytes bytes available
    //TODO check if there is bytes available memory in current
    //cell, go to next if not
    
    void *cell_ptr = NULL;
    return new_object(cell_ptr, NULL, bytes);
}


size_t h_gc(heap_t* h)
{
	return 0;
}

size_t h_gc_dbg(heap_t* h, bool unsafe_stack)
{
	return 0;
}

//TTODO
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
