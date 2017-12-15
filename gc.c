#include "gc.h"

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <windows.h>
#include <math.h>
#include <string.h>

#define MIN_HEAP_SIZE 0
#define MAX_HEAP_SIZE pow(2, 24)

/// The opaque data type holding all the heap data
typedef struct heap
{
	bool unsafe_stack;
	float gc_threshold;
	void* data;
} heap_t;

/// Create a new heap with bytes total size (including both spaces
/// and metadata), meaning strictly less than bytes will be
/// available for allocation.
///
/// \param bytes the total size of the heap in bytes
/// \param unsafe_stack true if pointers on the stack are to be considered unsafe pointers
/// \param gc_threshold the memory pressure at which gc should be triggered (1.0 = full memory)
/// \return the new heap
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
	void* p = (void*) 1;
	int result = 0;

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
	hp->data = hp + sizeof(heap_t);

	printf("allocated %d bytes of memory at: %d\n", b, hp);

	return hp;
}

/// Delete a heap.
///
/// \param h the heap
void h_delete(heap_t* h)
{
	#ifdef _WIN32
	__mingw_aligned_free(h);
	#else
	free(h);
	#endif
}

/// Delete a heap and trace, killing off stack pointers.
///
/// \param h the heap 
/// \param dbg_value a value to be written into every pointer into h on the stack
void h_delete_dbg(heap_t* h, void* dbg_value)
{
	
}

/// Allocate a new object on a heap with a given format string.
///
/// Valid characters in format strings are:
/// - 'i' -- for sizeof(int) bytes 'raw' data
/// - 'l' -- for sizeof(long) bytes 'raw' data
/// - 'f' -- for sizeof(float) bytes 'raw' data
/// - 'c' -- for sizeof(char) bytes 'raw' data
/// - 'd' -- for sizeof(double) bytes 'raw' data
/// - '*' -- for a sizeof(void* ) bytes pointer value
/// - '\0' -- null-character terminates the format string
///
/// \param h the heap
/// \param layout the format string
/// \return the newly allocated object
///
/// Note: the heap does* not* retain an alias to layout.
void* h_alloc_struct(heap_t* h, char* layout)
{
	
}

/// Allocate a new object on a heap with a given size.
///
/// Objects allocated with this function will* not* be 
/// further traced for pointers. 
///
/// \param h the heap
/// \param bytes the size in bytes
/// \return the newly allocated object
void* h_alloc_data(heap_t* h, size_t bytes)
{

}

/// Manually trigger garbage collection.
///
/// Garbage collection is otherwise run when an allocation is
/// impossible in the available consecutive free memory.
///
/// \param h the heap
/// \return the number of bytes collected
size_t h_gc(heap_t* h)
{
	return 0;
}

/// Manually trigger garbage collection with the ability to 
/// override the setting for how stack pointers are treated. 
/// 
/// Garbage collection is otherwise run when an allocation is
/// impossible in the available consecutive free memory.
///
/// \param h the heap
/// \param unsafe_stack true if pointers on the stack are to be considered unsafe pointers
/// \return the number of bytes collected
size_t h_gc_dbg(heap_t* h, bool unsafe_stack)
{
	return 0;
}

/// Returns the available free memory. 
///
/// \param h the heap
/// \return the available free memory. 
size_t h_avail(heap_t* h)
{
	return 0;
}

/// Returns the bytes currently in use by user structures. This
/// should not include the collector's own meta data. Notably,
/// this means that h_avail + h_used will not equal the size of
/// the heap passed to h_init.
/// 
/// \param h the heap
/// \return the bytes currently in use by user structures. 
size_t h_used(heap_t* h)
{
	return 0;
}