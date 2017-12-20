#include <stdio.h>
#include "gc.h"
#include <math.h>
#include "stack_traversal.h"
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
        

        printf("stack size: %i\n\n", stack_size());
	return 0;
}
