#include <stdio.h>
#include "gc.h"


typedef struct 
{
	bool mark_flag;
	void* data;
} object_t;

#define MAX_HEAP_SIZE 2^24
#define GARBAGE_COLLECTION_THRESHOLD 80

void trigger_garbage_collection()
{

}

void scan_program_for_roots()
{
	//scan stack
	//scan registers
	//scan static memory area
}

void free_marked_objects()
{

}


int main(int argc, char** argv)
{
	#ifdef _WIN32
	puts("windows");
	#endif
	
	#ifdef __linux__
	puts("linux");
	#endif
	
	#ifdef __unix__
	puts("unix");
	#endif

	return 0;
}